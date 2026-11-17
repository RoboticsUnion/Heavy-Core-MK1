#pragma once
#include <Arduino.h>

// Web Serial compatibility layer for pages served by the UNO R4 WiFi.
// Browser writes are posted to /send; PC-to-browser data is polled from /receive.
const char PAGE_BRIDGE_JS[] PROGMEM = R"GUIBRIDGE((() => {
    "use strict";

    const POLL_INTERVAL_MS = 75;
    let readController = null;
    let receivePolling = false;
    let receivePollActive = false;
    let portIsOpen = false;

    async function sendChunk(chunk) {
        let payload;
        if (typeof chunk === "string") {
            payload = chunk;
        } else if (chunk instanceof ArrayBuffer) {
            payload = new Uint8Array(chunk);
        } else if (ArrayBuffer.isView(chunk)) {
            payload = chunk;
        } else {
            payload = String(chunk ?? "");
        }

        const response = await fetch("/send", {
            method: "POST",
            headers: { "Content-Type": "application/octet-stream" },
            body: payload,
            cache: "no-store"
        });

        if (!response.ok) {
            const detail = await response.text().catch(() => "");
            throw new Error(`UNO R4 send failed (${response.status}): ${detail}`);
        }

        return response.text();
    }

    async function pollReceive() {
        if (!receivePollActive || receivePolling) return;
        receivePolling = true;

        try {
            const response = await fetch("/receive", {
                method: "GET",
                cache: "no-store"
            });

            if (!response.ok) {
                throw new Error(`Receive endpoint returned HTTP ${response.status}`);
            }

            const dropped = Number(response.headers.get("X-RX-Dropped") || 0);
            if (dropped > 0) {
                console.warn(`UNO R4 serial bridge dropped ${dropped} incoming byte(s).`);
            }

            const bytes = new Uint8Array(await response.arrayBuffer());
            if (bytes.length > 0 && readController && receivePollActive) {
                readController.enqueue(bytes);
            }
        } catch (error) {
            if (receivePollActive) {
                console.warn("UNO R4 serial receive poll failed:", error);
            }
        } finally {
            receivePolling = false;
            if (receivePollActive) {
                setTimeout(pollReceive, POLL_INTERVAL_MS);
            }
        }
    }

    const readable = new ReadableStream({
        start(controller) {
            readController = controller;
        },
        cancel() {
            receivePollActive = false;
            readController = null;
        }
    });

    const fakePort = {
        readable,
        writable: new WritableStream({
            write(chunk) {
                return sendChunk(chunk);
            }
        }),
        async open() {
            if (portIsOpen) return;
            portIsOpen = true;
            receivePollActive = true;
            pollReceive();
        },
        async close() {
            portIsOpen = false;
            receivePollActive = false;
        }
    };

    const serialShim = {
        async requestPort() { return fakePort; },
        async getPorts() { return portIsOpen ? [fakePort] : []; }
    };

    try {
        Object.defineProperty(navigator, "serial", {
            configurable: true,
            enumerable: true,
            value: serialShim
        });
    } catch (error) {
        console.error("Could not install UNO R4 Wi-Fi serial bridge:", error);
    }

    window.serialBridgeSend = sendChunk;
})();
)GUIBRIDGE";
