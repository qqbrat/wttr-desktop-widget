// ==WindhawkMod==
// @id              wttr-desktop-widget
// @name            wttr.in Desktop Weather Widget
// @description     Виджет погоды на рабочем столе (цветной вывод wttr.in)
// @version         1.4.0
// @author          Clause.ai & qqbrat
// @include         explorer.exe
// @compilerOptions -lwinhttp -lgdi32 -luser32 -ldwmapi -lshell32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Виджет погоды wttr.in

Показывает на рабочем столе прогноз погоды с сайта [wttr.in](https://wttr.in)
в том же виде, что и в терминале (с цветами и рамками).

* **Города:** в поле «Город» можно указать несколько через `;`, например
  `Kyiv;London;Tokyo`. Клик левой кнопкой по виджету переключает город, а ещё
  можно включить автоматическую смену каждые N секунд.
* **Расположение:** угол экрана, отступы в пикселях и номер монитора
  (0 - основной, 1, 2... - слева направо). Отступы можно масштабировать по DPI.
* **Свободное расположение:** выберите «Свободное» и тащите виджет мышью с зажатым
  `Ctrl`. Позиция запоминается.
* **Строка «Местоположение»:** можно скрыть или перенести на несколько строк.
* **Прозрачность:** «Непрозрачность фона» меняет только фон, текст остаётся чётким.
* **Режим «пропускать клики»:** мышь проходит сквозь виджет. В этом режиме нельзя
  ни перетащить виджет, ни открыть меню - выключите его, чтобы настроить.
* **Win+D / «Свернуть все окна»:** виджет остаётся на экране, когда показан рабочий
  стол. Когда открыто любое обычное окно, он лежит под ним.
* **Полноэкранные приложения:** виджет скрывается, пока запущена полноэкранная
  игра или видео, и не обновляется в это время.
* **Обновление:** по таймеру, после выхода из сна, а при ошибке сети - повторами
  через 15, 30, 60 и 120 секунд. Последний прогноз хранится на диске и показывается
  сразу после запуска, ещё до загрузки свежих данных.
* **Цвета:** палитра (обычная, яркая, приглушённая, «читаемая» с подсветкой тёмных
  цветов, одноцветная) и цвет основного текста.
* **Правая кнопка мыши:** меню (обновить, следующий город, сбросить позицию).
* Нужен моноширинный шрифт с символами рамок (Consolas, Cascadia Mono и т.п.).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- location: ""
  $name: Город (или несколько через ;)
  $description: Например Kyiv или Kyiv;London;Tokyo. Пусто - определить по IP.
- rotateSeconds: 0
  $name: Менять город каждые (секунд)
  $description: 0 - не менять автоматически (переключать кликом). Минимум 5.
- language: ru
  $name: Язык (код)
  $description: ru, uk, en, de, pl ...
- units: m
  $name: Единицы измерения
  $options:
  - m: Метрические (°C, км/ч)
  - M: Метрические, ветер в м/с
  - u: US (°F, mph)
- view: full
  $name: Режим отображения
  $options:
  - full: Сейчас + 3 дня
  - narrow: Сейчас + 3 дня, компактно
  - day2: Сейчас + 2 дня
  - day1: Сейчас + сегодня
  - current: Только текущая погода
- anchor: topright
  $name: Расположение на экране
  $options:
  - topleft: Левый верхний угол
  - topright: Правый верхний угол
  - bottomleft: Левый нижний угол
  - bottomright: Правый нижний угол
  - custom: Свободное (Ctrl + перетаскивание мышью)
- monitor: 0
  $name: Монитор
  $description: 0 - основной. 1, 2, ... - по порядку слева направо. Для свободного режима не используется.
- marginX: 20
  $name: Отступ по горизонтали (px)
  $description: От левого края для левых углов, от правого края для правых.
- marginY: 20
  $name: Отступ по вертикали (px)
  $description: От верхнего края для верхних углов, от нижнего края для нижних.
- scaleMargins: true
  $name: Масштабировать отступы по DPI
  $description: При масштабе Windows 150% отступ 20 станет 30 пикселей.
- clickThrough: false
  $name: Пропускать клики мыши сквозь виджет
  $description: В этом режиме не работают перетаскивание, меню и клик для смены города.
- ignoreShowDesktop: true
  $name: Не скрывать при "Свернуть все окна" (Win+D)
  $description: Виджет остаётся виден, когда показан рабочий стол.
- hideOnFullscreen: true
  $name: Скрывать при полноэкранных приложениях и играх
  $description: Пока запущено полноэкранное приложение, виджет скрыт и не обновляется.
- refreshMinutes: 30
  $name: Обновлять каждые (минут)
- fontName: Consolas
  $name: Шрифт
- fontSize: 10
  $name: Размер шрифта (pt)
- palette: default
  $name: Палитра цветов
  $options:
  - default: Обычная (как в терминале)
  - vivid: Яркая
  - soft: Приглушённая
  - readable: Читаемая (тёмные цвета осветляются)
  - mono: Одноцветная
- textColor: "CCCCCC"
  $name: Цвет основного текста (HEX)
  $description: Также используется для одноцветной палитры.
- locationLine: wrap
  $name: Строка «Местоположение» внизу
  $options:
  - wrap: Переносить на несколько строк (по ширине виджета)
  - hide: Скрыть
  - full: Показывать целиком (виджет станет шире)
- bgOpacity: 70
  $name: Непрозрачность фона (0-100 %)
  $description: 0 - фон полностью прозрачный, 100 - сплошной. Текст остаётся чётким.
- opacity: 100
  $name: Общая непрозрачность виджета (20-100 %)
  $description: Влияет и на текст тоже. Для прозрачного фона используйте параметр выше.
- background: "14171C"
  $name: Цвет фона (HEX)
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <winhttp.h>
#include <dwmapi.h>
#include <shellapi.h>

#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cwchar>
#include <memory>
#include <string>
#include <vector>

// ---------------------------------------------------------------- типы/глобали

struct Settings {
    std::wstring location, language, units, view, fontName, anchor, locationLine, palette;
    int fontSize = 10, refreshMin = 30, opacity = 100;
    int marginX = 20, marginY = 20, bgOpacity = 70, monitor = 0, rotateSec = 0;
    bool ignoreShowDesktop = true, scaleMargins = true, clickThrough = false,
         hideOnFullscreen = true;
    COLORREF bg = RGB(0x14, 0x17, 0x1C);
    COLORREF fg = RGB(204, 204, 204);
};

struct Cell {
    wchar_t ch;
    COLORREF color;
};
using Grid = std::vector<std::vector<Cell>>;

struct FetchJob {
    int idx;
    std::wstring path;
};
struct FetchResult {
    int idx;
    std::wstring path;
    bool ok;
    std::wstring text;  // тело ответа или текст ошибки
};

constexpr UINT WM_WEATHER = WM_APP + 1;
constexpr UINT WM_RELOAD = WM_APP + 2;
constexpr UINT_PTR TIMER_REFRESH = 1;
constexpr UINT_PTR TIMER_RETRY = 2;
constexpr UINT_PTR TIMER_ZORDER = 3;
constexpr UINT_PTR TIMER_ROTATE = 4;
constexpr int PAD = 10;
constexpr size_t MAX_CITIES = 8;
constexpr WCHAR kClassName[] = L"WindhawkWttrWidgetWnd";

Settings g_s;
Grid g_grid;  // то, что рисуем (после обработки строки местоположения)
Grid g_raw;   // разобранный вывод wttr.in как есть

// города и их данные
std::vector<std::wstring> g_cities;
std::vector<std::wstring> g_keys;    // путь запроса, по которому получен текст
std::vector<std::wstring> g_texts;   // последний успешный ответ (с ANSI-кодами)
std::vector<ULONGLONG> g_fetchTick;  // когда получен (0 - нужно обновить)
int g_cityIdx = 0;
int g_retryMs = 15000;
bool g_pendingRefetch = false;
bool g_hiddenFs = false;      // скрыт из-за полноэкранного приложения
bool g_staleWhileHidden = false;

HWND g_hwnd = nullptr;
HANDLE g_uiThread = nullptr;
DWORD g_uiTid = 0;
HANDLE g_readyEvent = nullptr;
HANDLE g_fetchThread = nullptr;
HANDLE g_mutex = nullptr;
std::atomic<bool> g_fetching{false};

bool g_promoted = false;  // временно поверх всех окон (пока показан рабочий стол)
HWINEVENTHOOK g_hookFg = nullptr, g_hookMin = nullptr;

HFONT g_font = nullptr;
int g_cw = 8, g_ch = 16;

// ---------------------------------------------------------------- настройки

static std::wstring GetStr(PCWSTR name) {
    PCWSTR v = Wh_GetStringSetting(name);
    std::wstring r = v ? v : L"";
    Wh_FreeStringSetting(v);
    return r;
}

static std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return L"";
    size_t b = s.find_last_not_of(L" \t\r\n");
    return s.substr(a, b - a + 1);
}

static int Clamp(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }

static COLORREF ParseHex(std::wstring s, COLORREF def) {
    s = Trim(s);
    if (!s.empty() && s[0] == L'#') s.erase(0, 1);
    if (s.empty()) return def;
    unsigned long v = wcstoul(s.c_str(), nullptr, 16);
    return RGB((v >> 16) & 255, (v >> 8) & 255, v & 255);
}

static void LoadSettings() {
    g_s.location = Trim(GetStr(L"location"));
    g_s.rotateSec = Wh_GetIntSetting(L"rotateSeconds");
    if (g_s.rotateSec < 0) g_s.rotateSec = 0;
    g_s.language = Trim(GetStr(L"language"));
    if (g_s.language.empty()) g_s.language = L"ru";
    g_s.units = GetStr(L"units");
    if (g_s.units.empty()) g_s.units = L"m";
    g_s.view = GetStr(L"view");

    g_s.anchor = Trim(GetStr(L"anchor"));
    if (g_s.anchor != L"topleft" && g_s.anchor != L"topright" && g_s.anchor != L"bottomleft" &&
        g_s.anchor != L"bottomright" && g_s.anchor != L"custom")
        g_s.anchor = L"topright";
    g_s.monitor = Clamp(Wh_GetIntSetting(L"monitor"), 0, 16);
    g_s.marginX = Clamp(Wh_GetIntSetting(L"marginX"), -5000, 5000);
    g_s.marginY = Clamp(Wh_GetIntSetting(L"marginY"), -5000, 5000);
    g_s.scaleMargins = Wh_GetIntSetting(L"scaleMargins") != 0;
    g_s.clickThrough = Wh_GetIntSetting(L"clickThrough") != 0;
    g_s.ignoreShowDesktop = Wh_GetIntSetting(L"ignoreShowDesktop") != 0;
    g_s.hideOnFullscreen = Wh_GetIntSetting(L"hideOnFullscreen") != 0;

    g_s.fontName = Trim(GetStr(L"fontName"));
    if (g_s.fontName.empty()) g_s.fontName = L"Consolas";
    g_s.fontSize = Clamp(Wh_GetIntSetting(L"fontSize"), 6, 40);
    g_s.refreshMin = Clamp(Wh_GetIntSetting(L"refreshMinutes"), 5, 24 * 60);

    g_s.palette = Trim(GetStr(L"palette"));
    if (g_s.palette != L"vivid" && g_s.palette != L"soft" && g_s.palette != L"readable" &&
        g_s.palette != L"mono")
        g_s.palette = L"default";
    g_s.fg = ParseHex(GetStr(L"textColor"), RGB(204, 204, 204));

    g_s.locationLine = Trim(GetStr(L"locationLine"));
    if (g_s.locationLine != L"hide" && g_s.locationLine != L"full") g_s.locationLine = L"wrap";
    g_s.bgOpacity = Clamp(Wh_GetIntSetting(L"bgOpacity"), 0, 100);
    g_s.opacity = Clamp(Wh_GetIntSetting(L"opacity"), 20, 100);
    g_s.bg = ParseHex(GetStr(L"background"), RGB(0x14, 0x17, 0x1C));
}

// ---------------------------------------------------------------- цвета и ANSI-разбор

static COLORREF Xterm256(int n) {
    static const BYTE base[16][3] = {
        {0, 0, 0},       {205, 49, 49},  {13, 188, 121},  {229, 229, 16},
        {36, 114, 200},  {188, 63, 188}, {17, 168, 205},  {204, 204, 204},
        {102, 102, 102}, {241, 76, 76},  {35, 209, 139},  {245, 245, 67},
        {59, 142, 234},  {214, 112, 214}, {41, 184, 219}, {255, 255, 255}};
    if (n < 0) n = 0;
    if (n < 16) return RGB(base[n][0], base[n][1], base[n][2]);
    if (n < 232) {
        n -= 16;
        int r = n / 36, g = (n / 6) % 6, b = n % 6;
        auto lv = [](int x) { return x == 0 ? 0 : 55 + x * 40; };
        return RGB(lv(r), lv(g), lv(b));
    }
    if (n > 255) n = 255;
    int gray = 8 + (n - 232) * 10;
    return RGB(gray, gray, gray);
}

// Применение выбранной палитры к цвету текста
static COLORREF MapColor(COLORREF c) {
    if (g_s.palette == L"default") return c;
    if (g_s.palette == L"mono") return g_s.fg;

    int r = GetRValue(c), g = GetGValue(c), b = GetBValue(c);
    int gray = (r * 30 + g * 59 + b * 11) / 100;
    if (g_s.palette == L"vivid") {
        r = gray + (r - gray) * 135 / 100;
        g = gray + (g - gray) * 135 / 100;
        b = gray + (b - gray) * 135 / 100;
    } else if (g_s.palette == L"soft") {
        r = gray + (r - gray) * 60 / 100;
        g = gray + (g - gray) * 60 / 100;
        b = gray + (b - gray) * 60 / 100;
    } else if (g_s.palette == L"readable") {
        const int target = 120;  // минимальная яркость
        if (gray < target) {
            int t = (target - gray) * 100 / (255 - gray);  // % смешивания с белым
            r += (255 - r) * t / 100;
            g += (255 - g) * t / 100;
            b += (255 - b) * t / 100;
        }
    }
    return RGB(Clamp(r, 0, 255), Clamp(g, 0, 255), Clamp(b, 0, 255));
}

static void ApplySgr(const std::vector<int>& p, COLORREF& cur, COLORREF def) {
    for (size_t k = 0; k < p.size(); k++) {
        int v = p[k];
        if (v == 0 || v == 39) {
            cur = def;
        } else if (v >= 30 && v <= 37) {
            cur = Xterm256(v - 30);
        } else if (v >= 90 && v <= 97) {
            cur = Xterm256(v - 90 + 8);
        } else if (v == 38 || v == 48) {
            bool fg = (v == 38);
            if (k + 2 < p.size() && p[k + 1] == 5) {
                if (fg) cur = Xterm256(p[k + 2]);
                k += 2;
            } else if (k + 4 < p.size() && p[k + 1] == 2) {
                if (fg) cur = RGB(p[k + 2] & 255, p[k + 3] & 255, p[k + 4] & 255);
                k += 4;
            }
        }
    }
}

static Grid ParseAnsi(const std::wstring& s, COLORREF initial = CLR_INVALID) {
    const COLORREF def = (initial == CLR_INVALID) ? g_s.fg : initial;
    Grid g(1);
    COLORREF cur = def;
    size_t i = 0;
    while (i < s.size()) {
        wchar_t c = s[i];
        if (c == 0x1B) {
            if (i + 1 < s.size() && s[i + 1] == L'[') {
                size_t j = i + 2;
                std::vector<int> params;
                int val = -1;
                while (j < s.size() && ((s[j] >= L'0' && s[j] <= L'9') || s[j] == L';')) {
                    if (s[j] == L';') {
                        params.push_back(val < 0 ? 0 : val);
                        val = -1;
                    } else {
                        val = (val < 0 ? 0 : val) * 10 + (s[j] - L'0');
                    }
                    j++;
                }
                params.push_back(val < 0 ? 0 : val);
                if (j < s.size() && s[j] == L'm') ApplySgr(params, cur, def);
                i = j + 1;
            } else {
                i++;
            }
            continue;
        }
        if (c == L'\n') {
            g.emplace_back();
        } else if (c != L'\r') {
            g.back().push_back({c == L'\t' ? L' ' : c, MapColor(cur)});
        }
        i++;
    }
    while (g.size() > 1 && g.back().empty()) g.pop_back();
    return g;
}

// ---------------------------------------------------------------- строка "Местоположение"

static size_t TrimmedLen(const std::vector<Cell>& line) {
    size_t e = line.size();
    while (e > 0 && line[e - 1].ch == L' ') e--;
    return e;
}

// Последняя строка вывода wttr.in вида "Местоположение: ... [lat,lon]"
static bool IsLocationLine(const std::vector<Cell>& line) {
    size_t e = TrimmedLen(line);
    if (e == 0 || line[e - 1].ch != L']') return false;
    for (size_t i = 0; i < e; i++)
        if (line[i].ch == L'[') return true;
    return false;
}

static Grid WrapLine(const std::vector<Cell>& src, size_t width) {
    Grid out;
    size_t e = TrimmedLen(src);
    size_t pos = 0;
    while (pos < e) {
        if (e - pos <= width) {
            out.emplace_back(src.begin() + pos, src.begin() + e);
            break;
        }
        size_t cut = 0;
        bool found = false;
        for (size_t i = pos + width; i > pos; i--) {
            if (src[i].ch == L' ') {
                cut = i;
                found = true;
                break;
            }
        }
        if (found) {
            out.emplace_back(src.begin() + pos, src.begin() + cut);
            pos = cut;
            while (pos < e && src[pos].ch == L' ') pos++;
        } else {
            out.emplace_back(src.begin() + pos, src.begin() + pos + width);
            pos += width;
        }
    }
    return out;
}

static Grid ProcessGrid(const Grid& raw) {
    Grid g = raw;
    if (g.empty() || g_s.locationLine == L"full") return g;

    size_t idx = g.size() - 1;
    while (idx > 0 && g[idx].empty()) idx--;
    if (!IsLocationLine(g[idx])) return g;

    if (g_s.locationLine == L"hide") {
        g.erase(g.begin() + idx);
        while (g.size() > 1 && g.back().empty()) g.pop_back();
        return g;
    }

    // wrap: ширина = ширина остального вывода (таблицы)
    size_t width = 0;
    for (size_t i = 0; i < g.size(); i++)
        if (i != idx) width = std::max(width, TrimmedLen(g[i]));
    if (width < 24) width = 24;

    Grid wrapped = WrapLine(g[idx], width);
    g.erase(g.begin() + idx);
    g.insert(g.begin() + idx, wrapped.begin(), wrapped.end());
    return g;
}

static void SetGrid(Grid raw) {
    g_raw = std::move(raw);
    g_grid = ProcessGrid(g_raw);
}

// ---------------------------------------------------------------- сеть

static std::string WideToUtf8(const std::wstring& w) {
    if (w.empty()) return "";
    int n = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string r(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), r.data(), n, nullptr, nullptr);
    return r;
}

static std::wstring BuildPath(const std::wstring& location) {
    std::string loc = WideToUtf8(location);
    std::string p = "/";
    for (unsigned char c : loc) {
        if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            c == '-' || c == '_' || c == '.' || c == '~') {
            p += (char)c;
        } else {
            char b[4];
            snprintf(b, sizeof(b), "%%%02X", c);
            p += b;
        }
    }
    p += "?";
    p += WideToUtf8(g_s.units);
    p += "&F";  // без строки "Follow @igor_chubin"
    std::string lang = WideToUtf8(g_s.language);
    std::string cleanLang;
    for (char c : lang)
        if (isalnum((unsigned char)c) || c == '-' || c == '_') cleanLang += c;
    if (!cleanLang.empty()) p += "&lang=" + cleanLang;

    if (g_s.view == L"narrow") p += "&n";
    else if (g_s.view == L"day2") p += "&2";
    else if (g_s.view == L"day1") p += "&1";
    else if (g_s.view == L"current") p += "&0";

    return std::wstring(p.begin(), p.end());
}

static bool HttpGet(const std::wstring& path, std::string& out, std::wstring& err) {
    bool ok = false;
    HINTERNET ses = WinHttpOpen(L"curl/8.5.0", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
                                WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!ses) {
        err = L"WinHttpOpen failed: " + std::to_wstring(GetLastError());
        return false;
    }
    WinHttpSetTimeouts(ses, 5000, 5000, 8000, 8000);
    HINTERNET con = WinHttpConnect(ses, L"wttr.in", INTERNET_DEFAULT_HTTPS_PORT, 0);
    HINTERNET req = con ? WinHttpOpenRequest(con, L"GET", path.c_str(), nullptr,
                                             WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES,
                                             WINHTTP_FLAG_SECURE)
                        : nullptr;
    if (req && WinHttpSendRequest(req, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA,
                                  0, 0, 0) &&
        WinHttpReceiveResponse(req, nullptr)) {
        DWORD status = 0, sz = sizeof(status);
        WinHttpQueryHeaders(req, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                            WINHTTP_HEADER_NAME_BY_INDEX, &status, &sz, WINHTTP_NO_HEADER_INDEX);
        if (status == 200) {
            DWORD avail = 0;
            while (WinHttpQueryDataAvailable(req, &avail) && avail > 0) {
                size_t old = out.size();
                out.resize(old + avail);
                DWORD got = 0;
                if (!WinHttpReadData(req, &out[old], avail, &got)) break;
                out.resize(old + got);
            }
            ok = !out.empty();
            if (!ok) err = L"Пустой ответ от wttr.in";
        } else {
            err = L"wttr.in вернул HTTP " + std::to_wstring(status);
        }
    } else {
        err = L"Нет соединения с wttr.in (код " + std::to_wstring(GetLastError()) + L")";
    }
    if (req) WinHttpCloseHandle(req);
    if (con) WinHttpCloseHandle(con);
    WinHttpCloseHandle(ses);
    return ok;
}

static DWORD WINAPI FetchThread(LPVOID param) {
    std::unique_ptr<FetchJob> job((FetchJob*)param);
    std::string body;
    std::wstring err;
    bool ok = HttpGet(job->path, body, err);

    auto* res = new FetchResult{job->idx, job->path, ok, L""};
    if (ok) {
        int n = MultiByteToWideChar(CP_UTF8, 0, body.data(), (int)body.size(), nullptr, 0);
        res->text.resize(n);
        MultiByteToWideChar(CP_UTF8, 0, body.data(), (int)body.size(), res->text.data(), n);
    } else {
        res->text = err;
    }
    g_fetching = false;
    if (!g_hwnd || !PostMessageW(g_hwnd, WM_WEATHER, 0, (LPARAM)res)) delete res;
    return 0;
}

// Запрос для текущего города. Если запрос уже идёт - повторится после него.
static void StartFetch() {
    if (g_cities.empty()) return;
    if (g_fetching.exchange(true)) {
        g_pendingRefetch = true;
        return;
    }
    if (g_fetchThread) {
        WaitForSingleObject(g_fetchThread, INFINITE);  // уже завершается
        CloseHandle(g_fetchThread);
        g_fetchThread = nullptr;
    }
    auto* job = new FetchJob{g_cityIdx, BuildPath(g_cities[g_cityIdx])};
    g_fetchThread = CreateThread(nullptr, 0, FetchThread, job, 0, nullptr);
    if (!g_fetchThread) {
        delete job;
        g_fetching = false;
    }
}

static bool NeedsRefresh(int i) {
    if (i < 0 || i >= (int)g_fetchTick.size()) return false;
    if (g_fetchTick[i] == 0) return true;
    ULONGLONG age = GetTickCount64() - g_fetchTick[i];
    return age + 2000 >= (ULONGLONG)g_s.refreshMin * 60000ULL;
}

// ---------------------------------------------------------------- города и кэш на диске

static std::vector<std::wstring> SplitCities(const std::wstring& s) {
    std::vector<std::wstring> out;
    size_t start = 0;
    while (true) {
        size_t p = s.find(L';', start);
        std::wstring part = Trim(s.substr(start, p == std::wstring::npos ? p : p - start));
        if (!part.empty() && out.size() < MAX_CITIES) out.push_back(part);
        if (p == std::wstring::npos) break;
        start = p + 1;
    }
    if (out.empty()) out.push_back(L"");  // определить по IP
    return out;
}

static void SaveCache(int i) {
    std::wstring t = g_texts[i];
    for (auto& c : t)
        if (c == 0x1B) c = 0xE000;  // ESC хранить в строке неудобно
    Wh_SetStringValue((L"ct" + std::to_wstring(i)).c_str(), t.c_str());
    Wh_SetStringValue((L"ck" + std::to_wstring(i)).c_str(), g_keys[i].c_str());
}

static bool LoadCache(int i, const std::wstring& key, std::wstring& out) {
    std::vector<wchar_t> kb(2048, 0);
    Wh_GetStringValue((L"ck" + std::to_wstring(i)).c_str(), kb.data(), kb.size());
    if (key != kb.data()) return false;
    std::vector<wchar_t> buf(65536, 0);
    Wh_GetStringValue((L"ct" + std::to_wstring(i)).c_str(), buf.data(), buf.size());
    out = buf.data();
    for (auto& c : out)
        if (c == 0xE000) c = 0x1B;
    return !out.empty();
}

// Пересобирает список городов; уже загруженные данные сохраняются
static void RebuildCities() {
    auto oldKeys = std::move(g_keys);
    auto oldTexts = std::move(g_texts);
    auto oldTick = std::move(g_fetchTick);

    g_cities = SplitCities(g_s.location);
    size_t n = g_cities.size();
    g_keys.assign(n, L"");
    g_texts.assign(n, L"");
    g_fetchTick.assign(n, 0);

    for (size_t i = 0; i < n; i++) {
        std::wstring key = BuildPath(g_cities[i]);
        g_keys[i] = key;
        bool found = false;
        for (size_t j = 0; j < oldKeys.size(); j++) {
            if (oldKeys[j] == key && !oldTexts[j].empty()) {
                g_texts[i] = oldTexts[j];
                g_fetchTick[i] = oldTick[j];
                found = true;
                break;
            }
        }
        if (!found) LoadCache((int)i, key, g_texts[i]);  // показываем сразу, обновим позже
    }
    if (g_cityIdx >= (int)n) g_cityIdx = 0;
}

// ---------------------------------------------------------------- отрисовка

static void Redraw(HWND h);

static void RebuildFont(HWND h) {
    if (g_font) DeleteObject(g_font);
    HDC dc = GetDC(h);
    int dpi = GetDeviceCaps(dc, LOGPIXELSY);
    g_font = CreateFontW(-MulDiv(g_s.fontSize, dpi, 72), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                         DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                         ANTIALIASED_QUALITY, FIXED_PITCH | FF_MODERN, g_s.fontName.c_str());
    HGDIOBJ old = SelectObject(dc, g_font);
    TEXTMETRICW tm{};
    GetTextMetricsW(dc, &tm);
    g_cw = tm.tmAveCharWidth > 0 ? tm.tmAveCharWidth : 8;
    g_ch = tm.tmHeight > 0 ? tm.tmHeight : 16;
    SelectObject(dc, old);
    ReleaseDC(h, dc);
}

static bool IsCustom() { return g_s.anchor == L"custom"; }

// Сохранённая позиция для свободного режима (с проверкой, что она на экране)
static void LoadSavedPos(int& x, int& y) {
    x = Wh_GetIntValue(L"posX", 50);
    y = Wh_GetIntValue(L"posY", 50);
    int vx = GetSystemMetrics(SM_XVIRTUALSCREEN), vy = GetSystemMetrics(SM_YVIRTUALSCREEN);
    int vw = GetSystemMetrics(SM_CXVIRTUALSCREEN), vh = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    if (x < vx || x > vx + vw - 50) x = vx + 50;
    if (y < vy || y > vy + vh - 50) y = vy + 50;
}

struct MonInfo {
    RECT work;
    RECT full;
    bool primary;
};

static BOOL CALLBACK MonEnumProc(HMONITOR m, HDC, LPRECT, LPARAM lp) {
    MONITORINFO mi{};
    mi.cbSize = sizeof(mi);
    if (GetMonitorInfoW(m, &mi))
        ((std::vector<MonInfo>*)lp)->push_back({mi.rcWork, mi.rcMonitor,
                                                (mi.dwFlags & MONITORINFOF_PRIMARY) != 0});
    return TRUE;
}

// Рабочая область выбранного монитора (0 - основной, 1.. - слева направо)
static RECT GetTargetWorkArea() {
    std::vector<MonInfo> v;
    EnumDisplayMonitors(nullptr, nullptr, MonEnumProc, (LPARAM)&v);
    if (v.empty()) {
        RECT wa{};
        SystemParametersInfoW(SPI_GETWORKAREA, 0, &wa, 0);
        return wa;
    }
    std::sort(v.begin(), v.end(), [](const MonInfo& a, const MonInfo& b) {
        return a.full.left != b.full.left ? a.full.left < b.full.left : a.full.top < b.full.top;
    });
    if (g_s.monitor >= 1 && g_s.monitor <= (int)v.size()) return v[g_s.monitor - 1].work;
    for (auto& m : v)
        if (m.primary) return m.work;
    return v[0].work;
}

static int ScaleMargin(int v) {
    if (!g_s.scaleMargins) return v;
    HDC dc = GetDC(nullptr);
    int dpi = GetDeviceCaps(dc, LOGPIXELSX);
    ReleaseDC(nullptr, dc);
    return MulDiv(v, dpi, 96);
}

// Меняет размер окна под текст и (в режиме угла) ставит его на нужное место.
static void ApplyLayout(HWND h) {
    size_t cols = 1;
    for (auto& line : g_grid) cols = std::max(cols, TrimmedLen(line));
    int w = (int)cols * g_cw + PAD * 2;
    int hh = (int)g_grid.size() * g_ch + PAD * 2;

    UINT flags = SWP_NOZORDER | SWP_NOACTIVATE;
    int x = 0, y = 0;
    if (IsCustom()) {
        flags |= SWP_NOMOVE;
    } else {
        RECT wa = GetTargetWorkArea();
        int mx = ScaleMargin(g_s.marginX), my = ScaleMargin(g_s.marginY);
        bool right = (g_s.anchor == L"topright" || g_s.anchor == L"bottomright");
        bool bottom = (g_s.anchor == L"bottomleft" || g_s.anchor == L"bottomright");
        x = right ? wa.right - w - mx : wa.left + mx;
        y = bottom ? wa.bottom - hh - my : wa.top + my;
    }
    SetWindowPos(h, nullptr, x, y, w, hh, flags);
    Redraw(h);
}

static void SetMessageGrid(const std::wstring& text, COLORREF color) {
    SetGrid(ParseAnsi(text, color));
}

// Показать данные выбранного города (из памяти/кэша) и при необходимости обновить
static void ShowCity(HWND h, int idx) {
    if (g_cities.empty()) return;
    g_cityIdx = ((idx % (int)g_cities.size()) + (int)g_cities.size()) % (int)g_cities.size();
    if (!g_texts[g_cityIdx].empty())
        SetGrid(ParseAnsi(g_texts[g_cityIdx]));
    else
        SetGrid(ParseAnsi(L"Загрузка погоды..."));
    ApplyLayout(h);
    if (NeedsRefresh(g_cityIdx) && !g_hiddenFs) StartFetch();
}

struct Dib {
    HDC dc = nullptr;
    HBITMAP bmp = nullptr;
    HGDIOBJ old = nullptr;
    DWORD* bits = nullptr;
};

static bool CreateDib(HDC ref, int w, int h, Dib& d) {
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;  // top-down
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    d.dc = CreateCompatibleDC(ref);
    if (!d.dc) return false;
    d.bmp = CreateDIBSection(ref, &bi, DIB_RGB_COLORS, (void**)&d.bits, nullptr, 0);
    if (!d.bmp) return false;
    d.old = SelectObject(d.dc, d.bmp);
    return true;
}

static void FreeDib(Dib& d) {
    if (d.dc && d.old) SelectObject(d.dc, d.old);
    if (d.bmp) DeleteObject(d.bmp);
    if (d.dc) DeleteDC(d.dc);
    d = Dib{};
}

static void DrawGrid(HDC dc, int w, int h, COLORREF bg, bool mask) {
    RECT rc{0, 0, w, h};
    HBRUSH br = CreateSolidBrush(bg);
    FillRect(dc, &rc, br);
    DeleteObject(br);

    HGDIOBJ oldFont = SelectObject(dc, g_font);
    SetBkMode(dc, TRANSPARENT);
    int y = PAD;
    for (auto& line : g_grid) {
        int x = PAD;
        for (auto& c : line) {
            if (c.ch != L' ') {
                SetTextColor(dc, mask ? RGB(255, 255, 255) : c.color);
                TextOutW(dc, x, y, &c.ch, 1);
            }
            x += g_cw;
        }
        y += g_ch;
    }
    SelectObject(dc, oldFont);
}

// Рисуем окно с попиксельной прозрачностью: фон имеет свою прозрачность,
// а текст остаётся непрозрачным. Для этого текст рисуется дважды: цветной
// (на фоне) и белый на чёрном (маска покрытия), из них считается альфа-канал.
static void Redraw(HWND h) {
    RECT wr;
    GetWindowRect(h, &wr);
    int w = wr.right - wr.left, hh = wr.bottom - wr.top;
    if (w <= 0 || hh <= 0) return;

    HDC scr = GetDC(nullptr);
    Dib a, b;
    if (CreateDib(scr, w, hh, a) && CreateDib(scr, w, hh, b)) {
        DrawGrid(a.dc, w, hh, g_s.bg, false);
        DrawGrid(b.dc, w, hh, RGB(0, 0, 0), true);
        GdiFlush();

        // минимум 1/255, иначе полностью прозрачные пиксели "пропускают" мышь
        int bgA = g_s.bgOpacity * 255 / 100;
        if (bgA < 1) bgA = 1;
        int br = GetRValue(g_s.bg), bgc = GetGValue(g_s.bg), bb = GetBValue(g_s.bg);

        size_t n = (size_t)w * hh;
        for (size_t i = 0; i < n; i++) {
            int c = (b.bits[i] >> 8) & 0xFF;  // покрытие текстом 0..255
            DWORD p = a.bits[i];
            int r = (p >> 16) & 0xFF, g = (p >> 8) & 0xFF, bl = p & 0xFF;
            int k = (255 - c) * (255 - bgA);  // 0..65025
            r -= k * br / 65025;
            g -= k * bgc / 65025;
            bl -= k * bb / 65025;
            int al = bgA + c * (255 - bgA) / 255;
            if (r < 0) r = 0;
            if (g < 0) g = 0;
            if (bl < 0) bl = 0;
            if (r > al) r = al;
            if (g > al) g = al;
            if (bl > al) bl = al;
            a.bits[i] = ((DWORD)al << 24) | ((DWORD)r << 16) | ((DWORD)g << 8) | (DWORD)bl;
        }

        SIZE sz{w, hh};
        POINT src{0, 0};
        BLENDFUNCTION bf{AC_SRC_OVER, 0, (BYTE)(g_s.opacity * 255 / 100), AC_SRC_ALPHA};
        UpdateLayeredWindow(h, scr, nullptr, &sz, a.dc, &src, 0, &bf, ULW_ALPHA);
    }
    FreeDib(a);
    FreeDib(b);
    ReleaseDC(nullptr, scr);
}

// ---------------------------------------------------------------- рабочий стол и полноэкранные окна

struct ShownCtx {
    HWND self;
    bool anyApp;
};

static BOOL CALLBACK EnumAppWnd(HWND w, LPARAM lp) {
    auto* c = (ShownCtx*)lp;
    if (w == c->self || !IsWindowVisible(w) || IsIconic(w)) return TRUE;
    LONG ex = GetWindowLongW(w, GWL_EXSTYLE);
    if (ex & (WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) return TRUE;
    WCHAR cls[32] = L"";
    GetClassNameW(w, cls, 32);
    if (!wcscmp(cls, L"Progman") || !wcscmp(cls, L"WorkerW")) return TRUE;
    DWORD cloaked = 0;
    if (SUCCEEDED(DwmGetWindowAttribute(w, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) && cloaked)
        return TRUE;
    RECT r;
    if (!GetWindowRect(w, &r) || r.right - r.left < 100 || r.bottom - r.top < 50) return TRUE;
    c->anyApp = true;  // нашли обычное видимое окно приложения
    return FALSE;
}

// Рабочий стол считается показанным, только если на экране нет ни одного
// обычного окна. Любое сомнение - "не показан" (виджет остаётся под окнами).
static bool IsDesktopShown(HWND self) {
    ShownCtx c{self, false};
    EnumWindows(EnumAppWnd, (LPARAM)&c);
    return !c.anyApp;
}

// Обычно виджет лежит под всеми окнами. Пока показан рабочий стол (Win+D),
// окно рабочего стола поднимается наверх и закрыло бы виджет, поэтому на это
// время виджет становится "поверх всех" и сразу возвращается вниз, как только
// появляется любое обычное окно.
static void UpdateZOrder(HWND h) {
    bool want = g_s.ignoreShowDesktop && !g_hiddenFs && IsDesktopShown(h);
    if (want && !g_promoted) {
        g_promoted = true;
        SetWindowPos(h, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    } else if (!want && g_promoted) {
        g_promoted = false;
        SetWindowPos(h, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

// Скрывает виджет, пока запущено полноэкранное приложение или игра
static void UpdateFullscreenState(HWND h) {
    bool fs = false;
    if (g_s.hideOnFullscreen) {
        QUERY_USER_NOTIFICATION_STATE st;
        if (SUCCEEDED(SHQueryUserNotificationState(&st)))
            fs = (st == QUNS_BUSY || st == QUNS_RUNNING_D3D_FULL_SCREEN ||
                  st == QUNS_PRESENTATION_MODE);
    }
    if (fs && !g_hiddenFs) {
        g_hiddenFs = true;
        if (g_promoted) {
            g_promoted = false;
            SetWindowPos(h, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }
        ShowWindow(h, SW_HIDE);
    } else if (!fs && g_hiddenFs) {
        g_hiddenFs = false;
        ShowWindow(h, SW_SHOWNOACTIVATE);
        if (g_staleWhileHidden) {
            g_staleWhileHidden = false;
            if (!g_cities.empty()) g_fetchTick[g_cityIdx] = 0;
            StartFetch();
        }
    }
}

static void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD, HWND, LONG, LONG, DWORD, DWORD) {
    if (g_hwnd) UpdateZOrder(g_hwnd);
}

// ---------------------------------------------------------------- окно

static void ApplyWindowSettings(HWND h) {
    RebuildFont(h);
    SetTimer(h, TIMER_REFRESH, (UINT)g_s.refreshMin * 60 * 1000, nullptr);
    SetTimer(h, TIMER_ZORDER, 200, nullptr);

    if (g_cities.size() > 1 && g_s.rotateSec >= 5)
        SetTimer(h, TIMER_ROTATE, (UINT)g_s.rotateSec * 1000, nullptr);
    else
        KillTimer(h, TIMER_ROTATE);

    // сквозные клики
    LONG ex = GetWindowLongW(h, GWL_EXSTYLE);
    LONG nex = g_s.clickThrough ? (ex | WS_EX_TRANSPARENT) : (ex & ~WS_EX_TRANSPARENT);
    if (nex != ex) SetWindowLongW(h, GWL_EXSTYLE, nex);

    BOOL excl = g_s.ignoreShowDesktop ? TRUE : FALSE;  // не скрывать при Aero Peek
    DwmSetWindowAttribute(h, DWMWA_EXCLUDED_FROM_PEEK, &excl, sizeof(excl));
    UpdateZOrder(h);

    if (IsCustom()) {
        int x, y;
        LoadSavedPos(x, y);
        SetWindowPos(h, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    ApplyLayout(h);
}

static void NextCity(HWND h) {
    if (g_cities.size() > 1) ShowCity(h, g_cityIdx + 1);
}

static LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    switch (m) {
        case WM_PAINT:
            ValidateRect(h, nullptr);
            return 0;
        case WM_ERASEBKGND:
            return 1;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_NCHITTEST:
            if (IsCustom() && (GetKeyState(VK_CONTROL) & 0x8000)) return HTCAPTION;  // Ctrl+drag
            return HTCLIENT;
        case WM_WINDOWPOSCHANGING: {
            auto* wp = (WINDOWPOS*)l;  // всегда под остальными окнами
            if (!g_promoted) {
                wp->hwndInsertAfter = HWND_BOTTOM;
                wp->flags &= ~SWP_NOZORDER;
            }
            break;
        }
        case WM_EXITSIZEMOVE: {
            RECT r;
            GetWindowRect(h, &r);
            Wh_SetIntValue(L"posX", r.left);
            Wh_SetIntValue(L"posY", r.top);
            return 0;
        }
        case WM_LBUTTONUP:  // клик - следующий город
            NextCity(h);
            if (g_s.rotateSec >= 5 && g_cities.size() > 1)
                SetTimer(h, TIMER_ROTATE, (UINT)g_s.rotateSec * 1000, nullptr);
            return 0;
        case WM_RBUTTONUP: {
            HMENU menu = CreatePopupMenu();
            AppendMenuW(menu, MF_STRING, 1, L"Обновить");
            if (g_cities.size() > 1) AppendMenuW(menu, MF_STRING, 3, L"Следующий город");
            if (IsCustom()) AppendMenuW(menu, MF_STRING, 2, L"Сбросить позицию");
            POINT pt;
            GetCursorPos(&pt);
            SetForegroundWindow(h);
            int cmd = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, pt.x, pt.y, 0, h,
                                     nullptr);
            PostMessageW(h, WM_NULL, 0, 0);
            DestroyMenu(menu);
            if (cmd == 1) {
                if (!g_cities.empty()) g_fetchTick[g_cityIdx] = 0;
                StartFetch();
            } else if (cmd == 2) {
                SetWindowPos(h, nullptr, 50, 50, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
                Wh_SetIntValue(L"posX", 50);
                Wh_SetIntValue(L"posY", 50);
            } else if (cmd == 3) {
                NextCity(h);
            }
            return 0;
        }
        case WM_DISPLAYCHANGE:
            ApplyLayout(h);
            return 0;
        case WM_SETTINGCHANGE:
            if (w == SPI_SETWORKAREA) ApplyLayout(h);
            return 0;
        case WM_POWERBROADCAST:
            if (w == PBT_APMRESUMEAUTOMATIC || w == PBT_APMRESUMESUSPEND) {
                // после сна сеть поднимается не сразу - обновляемся чуть позже
                if (!g_cities.empty()) g_fetchTick[g_cityIdx] = 0;
                SetTimer(h, TIMER_RETRY, 8000, nullptr);
            }
            return TRUE;
        case WM_TIMER:
            if (w == TIMER_ZORDER) {
                UpdateFullscreenState(h);
                UpdateZOrder(h);
                return 0;
            }
            if (w == TIMER_ROTATE) {
                if (!g_hiddenFs) NextCity(h);
                return 0;
            }
            if (w == TIMER_REFRESH) {
                if (g_hiddenFs) {
                    g_staleWhileHidden = true;
                } else {
                    if (!g_cities.empty()) g_fetchTick[g_cityIdx] = 0;
                    StartFetch();
                }
            } else if (w == TIMER_RETRY) {
                KillTimer(h, TIMER_RETRY);
                if (g_hiddenFs) g_staleWhileHidden = true;
                else StartFetch();
            }
            return 0;
        case WM_WEATHER: {
            std::unique_ptr<FetchResult> r((FetchResult*)l);
            bool valid = r->idx >= 0 && r->idx < (int)g_cities.size() &&
                         BuildPath(g_cities[r->idx]) == r->path;  // настройки могли смениться
            if (valid) {
                if (r->ok) {
                    g_texts[r->idx] = r->text;
                    g_keys[r->idx] = r->path;
                    g_fetchTick[r->idx] = GetTickCount64();
                    SaveCache(r->idx);
                    g_retryMs = 15000;
                    KillTimer(h, TIMER_RETRY);
                    if (r->idx == g_cityIdx) {
                        SetGrid(ParseAnsi(r->text));
                        ApplyLayout(h);
                    }
                } else if (r->idx == g_cityIdx) {
                    if (g_texts[r->idx].empty()) {
                        SetMessageGrid(r->text, RGB(241, 76, 76));
                        ApplyLayout(h);
                    }
                    // повтор с нарастающей паузой: 15, 30, 60, 120 секунд
                    SetTimer(h, TIMER_RETRY, (UINT)g_retryMs, nullptr);
                    g_retryMs = std::min(g_retryMs * 2, 120000);
                }
            }
            if (g_pendingRefetch) {
                g_pendingRefetch = false;
                if (NeedsRefresh(g_cityIdx)) StartFetch();
            }
            return 0;
        }
        case WM_RELOAD:
            LoadSettings();
            RebuildCities();
            ApplyWindowSettings(h);
            UpdateFullscreenState(h);
            ShowCity(h, g_cityIdx);
            return 0;
    }
    return DefWindowProcW(h, m, w, l);
}

static DWORD WINAPI UiThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);  // создать очередь

    HINSTANCE inst = GetModuleHandleW(nullptr);
    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = inst;
    wc.lpszClassName = kClassName;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassW(&wc);

    RebuildCities();

    int x, y;
    LoadSavedPos(x, y);  // для угловых режимов окно всё равно переставит ApplyLayout

    g_hwnd = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE, kClassName, L"",
                             WS_POPUP, x, y, 300, 100, nullptr, nullptr, inst, nullptr);
    if (g_hwnd) {
        ApplyWindowSettings(g_hwnd);
        ShowCity(g_hwnd, 0);
        ShowWindow(g_hwnd, SW_SHOWNOACTIVATE);
        SetWindowPos(g_hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        g_hookFg = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr,
                                   WinEventProc, 0, 0, WINEVENT_OUTOFCONTEXT);
        g_hookMin = SetWinEventHook(EVENT_SYSTEM_MINIMIZESTART, EVENT_SYSTEM_MINIMIZEEND, nullptr,
                                    WinEventProc, 0, 0, WINEVENT_OUTOFCONTEXT);
    }
    SetEvent(g_readyEvent);

    if (g_hwnd) {
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        if (g_hookFg) UnhookWinEvent(g_hookFg);
        if (g_hookMin) UnhookWinEvent(g_hookMin);
        g_hookFg = g_hookMin = nullptr;
        KillTimer(g_hwnd, TIMER_REFRESH);
        KillTimer(g_hwnd, TIMER_RETRY);
        KillTimer(g_hwnd, TIMER_ZORDER);
        KillTimer(g_hwnd, TIMER_ROTATE);
        HWND h = g_hwnd;
        g_hwnd = nullptr;
        DestroyWindow(h);
    }

    if (g_fetchThread) {
        WaitForSingleObject(g_fetchThread, 15000);
        CloseHandle(g_fetchThread);
        g_fetchThread = nullptr;
    }
    if (g_font) {
        DeleteObject(g_font);
        g_font = nullptr;
    }
    UnregisterClassW(kClassName, inst);
    return 0;
}

// ---------------------------------------------------------------- Windhawk

BOOL Wh_ModInit() {
    // Только один экземпляр (на случай нескольких процессов explorer.exe)
    g_mutex = CreateMutexW(nullptr, TRUE, L"Local\\WindhawkWttrWidgetMutex");
    if (!g_mutex) return FALSE;
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(g_mutex);
        g_mutex = nullptr;
        return TRUE;
    }

    LoadSettings();
    g_readyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThread, nullptr, 0, &g_uiTid);
    if (!g_uiThread) {
        CloseHandle(g_readyEvent);
        CloseHandle(g_mutex);
        g_mutex = nullptr;
        return FALSE;
    }
    WaitForSingleObject(g_readyEvent, 5000);
    return TRUE;
}

void Wh_ModSettingsChanged() {
    if (g_hwnd) PostMessageW(g_hwnd, WM_RELOAD, 0, 0);
}

void Wh_ModUninit() {
    if (g_uiThread) {
        PostThreadMessageW(g_uiTid, WM_QUIT, 0, 0);
        WaitForSingleObject(g_uiThread, INFINITE);
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }
    if (g_readyEvent) {
        CloseHandle(g_readyEvent);
        g_readyEvent = nullptr;
    }
    if (g_mutex) {
        ReleaseMutex(g_mutex);
        CloseHandle(g_mutex);
        g_mutex = nullptr;
    }
}
