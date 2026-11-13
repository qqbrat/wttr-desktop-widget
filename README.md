# wttr-desktop-widget
wttr.in Weather Widget
Displays the weather forecast from wttr.in on your desktop, just like in the terminal (with colors and frames).

Cities: You can specify multiple cities in the "City" field, separated by a ;, for example, Kyiv; London; Tokyo. Left-clicking on the widget switches between cities, and you can also enable automatic switching every N seconds.
Position: Screen corner, pixel margins, and monitor number (0 - primary, 1, 2... - left to right). Margins can be scaled by DPI.
Free position: Select "Free" and drag the widget with your mouse while holding down Ctrl. The position is remembered.
"Location" line: Can be hidden or wrapped across multiple lines.
Transparency: "Background opacity" changes only the background; the text remains legible.
"Skip clicks" mode: The mouse moves through the widget. In this mode, you can't drag the widget or open the menu; disable it to configure it.
Win+D / "Minimize all windows": The widget remains on the screen when the desktop is shown. When any regular window is open, it appears underneath it.
Full-screen apps: The widget is hidden while a full-screen game or video is running and is not updated during this time.
Updates: by timer, after waking from sleep, and in case of a network error, repeated after 15, 30, 60, and 120 seconds. The latest forecast is stored on disk and is displayed immediately after launch, before the latest data is downloaded.
Colors: Palette (normal, bright, muted, "readable" with dark color highlighting, single-color) and main text color.
Right-click: Menu (refresh, next city, reset position).
A monospaced font with frame symbols is required (Consolas, Cascadia Mono, etc.).
