#pragma once
#include <Arduino.h>

const char PAGE_BRIDGE_JS[] PROGMEM = R"GUIBRIDGE(/*
 * Browser compatibility layer for the existing HTML_GUI website.
 * It emulates only the Web Serial pieces used by the pages. No COM port
 * is opened by the browser: each write is posted to this Arduino's /send URL.
 */
(() => {
    "use strict";

    async function sendChunk(chunk) {
        let text;
        if (typeof chunk === "string") {
            text = chunk;
        } else if (chunk instanceof ArrayBuffer) {
            text = new TextDecoder().decode(new Uint8Array(chunk));
        } else if (ArrayBuffer.isView(chunk)) {
            text = new TextDecoder().decode(chunk);
        } else {
            text = String(chunk ?? "");
        }

        const response = await fetch("/send", {
            method: "POST",
            headers: { "Content-Type": "text/plain; charset=utf-8" },
            body: text,
            cache: "no-store"
        });
        if (!response.ok) {
            const detail = await response.text().catch(() => "");
            throw new Error(`Arduino send failed (${response.status}) ${detail}`);
        }
        return response.text();
    }

    let currentReadable = null;
    const fakePort = {
        readable: new ReadableStream({
            start(controller) {
                currentReadable = controller;
                // No PC-to-web receive channel is enabled in this first version.
                // The stream remains open so the existing page reader loops do not fail.
            },
            cancel() { currentReadable = null; }
        }),
        writable: new WritableStream({
            write(chunk) { return sendChunk(chunk); }
        }),
        async open() { this.isOpen = true; },
        async close() { this.isOpen = false; }
    };

    const serialShim = {
        async requestPort() { return fakePort; },
        async getPorts() { return []; }
    };

    try {
        Object.defineProperty(navigator, "serial", {
            configurable: true,
            enumerable: true,
            value: serialShim
        });
    } catch (error) {
        console.error("Could not install Arduino Wi-Fi serial bridge:", error);
    }

    window.serialBridgeSend = sendChunk;
})();
)GUIBRIDGE";
