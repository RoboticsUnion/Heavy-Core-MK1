def help_GUI():
    import tkinter as tk
    import state

    # ---------------- WINDOW ----------------
    root = tk.Tk()
    root.title("User Manual")
    root.geometry("800x800")

    # ---------------- NAVIGATION ----------------
    def show_frame(frame):
        frame.tkraise()

    # ---------------- CONTAINER ----------------
    container = tk.Frame(root)
    container.pack(fill="both", expand=True)

    container.grid_rowconfigure(0, weight=0)  # Menü
    container.grid_rowconfigure(1, weight=1)  # Inhalt
    container.grid_columnconfigure(0, weight=1)

    # ---------------- MENU ----------------
    menu = tk.Frame(container)
    menu.grid(row=0, column=0)

    # Frames müssen VOR Buttons existieren
    frame1 = tk.Frame(container)
    frame2 = tk.Frame(container)
    frame3 = tk.Frame(container)
    frame4 = tk.Frame(container)
    frame5 = tk.Frame(container)

    for frame in (frame1, frame2, frame3, frame4, frame5):
        frame.grid(row=1, column=0, sticky="nsew")

    btn1 = tk.Button(menu, text="cmd-basics", command=lambda: show_frame(frame1))
    btn2 = tk.Button(menu, text="cmd-commands", command=lambda: show_frame(frame2))
    btn3 = tk.Button(menu, text="cmd-help", command=lambda: show_frame(frame3))
    btn4 = tk.Button(menu, text="GUI-basics", command=lambda: show_frame(frame4))
    btn5 = tk.Button(menu, text="Content-Creation", command=lambda: show_frame(frame5))

    btn1.pack(side="left", padx=10, pady=10)
    btn2.pack(side="left", padx=10, pady=10)
    btn3.pack(side="left", padx=10, pady=10)
    btn4.pack(side="left", padx=10, pady=10)
    btn5.pack(side="left", padx=10, pady=10)

    # ---------------- TITLE ----------------
    def center_label(frame, text):
        inner = tk.Frame(frame)
        inner.place(relx=0.5, rely=0.08, anchor="center")

        tk.Label(
            inner,
            text=text,
            font=("Arial", 14),
            wraplength=700,
            justify="center"
        ).pack()

    # ---------------- SCROLL TEXT ----------------
    def center_label_normal(frame, text):
        outer = tk.Frame(frame)
        outer.place(
            relx=0.5,
            rely=0.55,
            anchor="center",
            relwidth=0.92,
            relheight=0.78
        )

        text_box = tk.Text(
            outer,
            font=("Arial", 10),
            wrap="word",
            padx=10,
            pady=10
        )

        scroll_y = tk.Scrollbar(
            outer,
            orient="vertical",
            command=text_box.yview
        )

        scroll_x = tk.Scrollbar(
            outer,
            orient="horizontal",
            command=text_box.xview
        )

        text_box.configure(
            yscrollcommand=scroll_y.set,
            xscrollcommand=scroll_x.set
        )

        text_box.grid(row=0, column=0, sticky="nsew")
        scroll_y.grid(row=0, column=1, sticky="ns")
        scroll_x.grid(row=1, column=0, sticky="ew")

        outer.grid_rowconfigure(0, weight=1)
        outer.grid_columnconfigure(0, weight=1)

        text_box.insert("1.0", text)
        text_box.configure(state="disabled")

    # ---------------- CONTENT ----------------
    center_label(frame1, "Page 1\nCMD - Basics")
    center_label(frame2, "Page 2\nCMD - Commands")
    center_label(frame3, "Page 3\nCMD - Help")
    center_label(frame4, "Page 4\nGUI - Basic")
    center_label(frame5, "Page 5\nContent Creation")

    center_label_normal(frame1, state.basic_text)
    center_label_normal(frame2, state.commands_text)
    center_label_normal(frame3, state.help_text)
    center_label_normal(frame4, state.gui_text)
    center_label_normal(frame5, state.content_text)

    # ---------------- START ----------------
    show_frame(frame1)

    root.mainloop()
