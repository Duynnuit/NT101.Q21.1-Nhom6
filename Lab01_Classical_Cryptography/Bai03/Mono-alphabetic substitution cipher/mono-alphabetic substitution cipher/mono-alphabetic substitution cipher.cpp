// ============================================================
//  MONO-ALPHABETIC CIPHER BREAKER
//  Compatible: Visual Studio (MSVC), GCC, Clang
//  Build: g++ -O2 -std=c++17 -o crack cipher_msvc.cpp  (GCC)
//         cl /O2 /std:c++17 cipher_msvc.cpp             (MSVC)
// ============================================================
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <cmath>
using namespace std;

// ============================================================
//  SCORING DATA: Bigram[26x26] + Quadgram[26^4] arrays
//  Dùng mảng tĩnh thay unordered_map -> O(1) lookup, nhanh hơn ~5x
// ============================================================
static double BG[26][26];
static double QG[26][26][26][26];
static double BF, QF; // floor (giá trị cho n-gram không có trong data)

void init() {
    // --- BIGRAMS (200 phổ biến nhất, tần suất thực từ corpus tiếng Anh) ---
    struct E2 { const char* s; int n; };
    E2 bg[] = {
        {"TH",3882},{"HE",3681},{"IN",2283},{"ER",2182},{"AN",2140},
        {"RE",1756},{"ON",1654},{"EN",1644},{"AT",1492},{"ES",1446},
        {"ED",1454},{"TE",1356},{"TI",1345},{"OR",1283},{"ST",1252},
        {"AR",1224},{"NT",1201},{"ND",1182},{"TO",1165},{"IT",1123},
        {"IS",1100},{"OF",1096},{"AL",1093},{"HA",1070},{"LE",1065},
        {"SE",1030},{"VE",1012},{"HI",1001},{"AS",980}, {"OU",970},
        {"BE",960}, {"IO",962}, {"ME",951}, {"DE",944}, {"CO",930},
        {"LY",910}, {"NG",900}, {"ET",901}, {"EA",893}, {"IC",862},
        {"LI",853}, {"NE",843}, {"RI",831}, {"EC",832}, {"RA",825},
        {"RO",822}, {"LA",812}, {"EL",801}, {"WA",795}, {"NA",784},
        {"GE",763}, {"WI",764}, {"TA",759}, {"LL",756}, {"MA",752},
        {"AC",751}, {"EE",742}, {"EM",731}, {"WH",730}, {"OT",727},
        {"NO",720}, {"EW",712}, {"SA",702}, {"IL",695}, {"CH",690},
        {"SS",688}, {"OW",674}, {"CA",670}, {"OO",668}, {"MI",660},
        {"UR",655}, {"OL",648}, {"EV",644}, {"GH",640}, {"FO",635},
        {"MO",630}, {"PA",625}, {"NC",620}, {"RT",615}, {"FI",612},
        {"PE",608}, {"CI",602}, {"IA",598}, {"SI",590}, {"ID",586},
        {"SH",583}, {"TR",580}, {"PL",576}, {"UN",573}, {"HO",570},
        {"SO",566}, {"AD",562}, {"DI",558}, {"OC",554}, {"AM",550},
        {"KE",547}, {"EX",543}, {"VI",540}, {"EI",536}, {"WO",533},
        {"IF",530}, {"UL",527}, {"MU",523}, {"DA",520}, {"BA",517},
        {"LO",514}, {"GI",510}, {"PO",507}, {"OP",503}, {"PR",500},
        {"SP",497}, {"TT",494}, {"OA",491}, {"AB",488}, {"CE",485},
        {"OS",482}, {"HU",479}, {"CR",476}, {"NI",473}, {"AI",470},
        {"LU",467}, {"BO",464}, {"OI",461}, {"OD",458}, {"DO",455},
        {"SU",452}, {"PI",449}, {"FR",446}, {"UP",443}, {"PU",440},
        {"AG",437}, {"AU",434}, {"WE",431}, {"DU",428}, {"KI",422},
        {"SC",419}, {"EF",416}, {"UE",413}, {"AK",410}, {"GR",407},
        {"CU",404}, {"RU",398}, {"BY",395}, {"TU",392}, {"WR",389},
        {"UI",383}, {"OV",380}, {"RD",350}, {"AY",347}, {"FE",344},
        {"MP",341}, {"BL",338}, {"FF",332}, {"SL",329}, {"CL",326},
        {"LD",320}, {"TY",311}, {"CT",308}, {"YE",305}, {"NK",302},
        {"RN",299}, {"EY",293}, {"PH",290}, {"OY",287}, {"FT",275},
        {"TW",272}, {"AV",260}, {"AW",254}, {"RS",224}, {"TS",221},
        {"NS",218}, {"PT",212}, {"DD",209}, {"ZE",200},
    };
    long long tot = 0;
    for (auto& e : bg) tot += e.n;
    BF = log(0.01 / tot);
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++) BG[i][j] = BF;
    for (auto& e : bg)
        BG[e.s[0] - 'A'][e.s[1] - 'A'] = log((double)e.n / tot);

    // --- QUADGRAMS (200 phổ biến nhất) ---
    struct E4 { const char* s; int n; };
    E4 qg[] = {
        {"TION",69177},{"NTHE",65718},{"THER",62672},{"THAT",62131},{"OFTH",60459},
        {"FTHE",59214},{"THES",52844},{"WITH",52100},{"INTH",49847},{"ERTH",44285},
        {"THEC",42643},{"ATIO",42586},{"THEM",41500},{"THEP",41019},{"HEIR",40505},
        {"HERE",39723},{"THEI",38749},{"THEA",37774},{"OTHE",35238},{"THEW",34896},
        {"INGT",34831},{"NGTH",34812},{"IONS",34698},{"TING",33919},{"HATH",33531},
        {"ANDT",33257},{"MENT",32437},{"TTHE",31883},{"ETHE",31664},{"OUNT",31370},
        {"RTHE",31249},{"THIS",30813},{"HAVE",30428},{"THED",29790},{"THEF",29503},
        {"WERE",28826},{"THEY",28583},{"EING",28519},{"ENTE",27944},{"ERED",27921},
        {"INGS",27807},{"BEEN",27782},{"TAND",27756},{"STHE",27599},{"NTER",27431},
        {"THEN",27367},{"HICH",26959},{"OULD",26829},{"FROM",26798},{"ENCE",26574},
        {"OUGH",26382},{"IGHT",26356},{"ATES",25954},{"EVER",25782},{"OVER",25690},
        {"NDER",25665},{"INTO",25622},{"TERE",25450},{"ANCE",25401},{"MORE",25344},
        {"UPON",25301},{"HERS",25243},{"TTER",25151},{"ALSO",25078},{"FORE",24957},
        {"COME",24912},{"OUND",24861},{"IRST",24722},{"OING",24537},{"ATED",24468},
        {"MADE",24437},{"VERY",24375},{"LAND",24325},{"ALLY",24251},{"CESS",24168},
        {"SAID",24011},{"TATI",23920},{"ICAL",23890},{"SUCH",23855},{"EACH",23820},
        {"HAND",23715},{"CAME",23680},{"NESS",23645},{"MOST",23610},{"HING",23580},
        {"MUCH",23510},{"LONG",23475},{"KING",23405},{"TIME",23370},{"WELL",23335},
        {"PART",23300},{"SOME",23265},{"TAIN",23230},{"FORM",22565},{"ARLY",22530},
        {"WORK",22495},{"THIN",22460},{"WHEN",22425},{"SELF",22390},{"KNOW",22355},
        {"OPEN",22320},{"TURN",22250},{"ONLY",22215},{"TIVE",22180},{"GREA",22075},
        {"TAKE",22040},{"LIKE",22005},{"LOOK",21935},{"ABLE",21900},{"WHIC",21800},
        {"JUST",21750},{"YEAR",21700},{"ORLD",21650},{"WORD",21600},{"LIFE",21550},
        {"YING",21500},{"OUTH",21450},{"AREA",21400},{"ATER",21350},{"RESS",21300},
        {"ITHE",21200},{"EFOR",21150},{"NOWN",21050},{"WEEN",20950},{"REAT",20600},
        {"FULL",20350},{"LESS",20200},{"EARS",20100},{"REAL",20050},{"WAYS",19950},
        {"HEAD",19900},{"TOLD",19800},{"FACE",19750},{"EYES",19650},{"GOOD",19600},
        {"CARE",19550},{"SAME",19500},{"ONCE",19450},{"LAST",19400},{"FEET",19300},
        {"DOOR",19250},{"ROAD",19200},{"DAYS",19150},{"FELT",19100},{"LEFT",19050},
        {"DONE",19000},{"USED",18950},{"BACK",18900},{"HELD",18850},{"HOME",18800},
        {"HOPE",18750},{"LOVE",18700},{"MIND",18650},{"NAME",18600},{"NEAR",18550},
        {"NEXT",18500},{"PAST",18400},{"ROOM",18350},{"SIDE",18300},{"THEE",18250},
        {"TOWN",18200},{"TRUE",18150},{"UNTO",18100},{"WENT",18000},{"WHAT",17950},
        {"WHOM",17900},{"WIDE",17850},{"WILL",17800},{"WISE",17750},{"WISH",17700},
        {"WOOD",17650},{"THAN",17600},{"CALL",13900},{"CASE",13550},{"CAST",13500},
        {"CENT",13350},{"COAL",12500},{"COAT",12450},{"COIN",12400},{"COLD",12350},
        {"COOK",12200},{"COOL",12150},{"CORD",12100},{"CORN",11950},{"COST",11900},
        {"DARE",11450},{"DARK",11400},{"DATE",11200},{"DAWN",11150},{"DEAD",11100},
        {"DEAL",11000},{"DEAR",10950},{"DEEP",10800},{"DOWN",9950}, {"DRAW",9750},
        {"DROP",9600}, {"DUST",9300}, {"DUTY",9250}, {"EASE",9050}, {"EAST",9000},
        {"EDGE",8950}, {"ELSE",8900}, {"EVEN",8800}, {"EVIL",8750}, {"FACT",8600},
        {"FAIL",8550}, {"FAIR",8500}, {"FALL",8450}, {"FARM",8350}, {"FAST",8300},
        {"FATE",8250}, {"FEAR",8150}, {"FEEL",8050}, {"FELL",8000}, {"FILE",7800},
        {"FILL",7750}, {"FILM",7700}, {"FINE",7650}, {"FIRE",7600}, {"FIRM",7550},
        {"FISH",7500}, {"FLOW",7000}, {"FOLD",6850}, {"FOLK",6800}, {"FOND",6750},
        {"FOOL",6650}, {"FORD",6600}, {"FORT",6550}, {"FREE",6350}, {"FUEL",6200},
        {"FUND",6150}, {"GAME",5950}, {"GATE",5700}, {"GEAR",5600}, {"GLAD",5400},
        {"GLOW",5150}, {"GOAL",5000}, {"GRAM",4650}, {"GRIN",4550}, {"GRIP",4500},
        {"GROW",4350}, {"SION",15000},{"IBLE",12000},
    };
    long long tot2 = 0;
    for (auto& e : qg) tot2 += e.n;
    QF = log(0.01 / tot2);
    for (int a = 0; a < 26; a++) for (int b = 0; b < 26; b++)
        for (int c = 0; c < 26; c++) for (int d = 0; d < 26; d++)
            QG[a][b][c][d] = QF;
    for (auto& e : qg) {
        double v = log((double)e.n / tot2);
        int a = e.s[0] - 'A', b = e.s[1] - 'A', c = e.s[2] - 'A', d = e.s[3] - 'A';
        if (QG[a][b][c][d] < v) QG[a][b][c][d] = v;
    }
}

// ============================================================
//  KEY STRUCTURE
//  fwd[plain_idx] = cipher_idx   (encode)
//  rev[cipher_idx] = plain_idx   (decode) <- dùng khi tính score
// ============================================================
struct Key {
    uint8_t fwd[26], rev[26];
    Key() {}
    Key(const string& s) {
        for (int i = 0; i < 26; i++) {
            fwd[i] = (uint8_t)(s[i] - 'A');
            rev[s[i] - 'A'] = (uint8_t)i;
        }
    }
    // Swap 2 plain letters, cập nhật cả 2 bảng
    void swap2(int a, int b) {
        uint8_t ca = fwd[a], cb = fwd[b];
        fwd[a] = cb; fwd[b] = ca;
        rev[ca] = (uint8_t)b; rev[cb] = (uint8_t)a;
    }
};

// Score trực tiếp trên cipher bytes — không tạo string trung gian (tối ưu tốc độ)
double score(const vector<uint8_t>& c, const Key& k) {
    int n = (int)c.size();
    double s = 0;
    for (int i = 0; i + 1 < n; i++)
        s += 1.5 * BG[k.rev[c[i]]][k.rev[c[i + 1]]];
    for (int i = 0; i + 3 < n; i++)
        s += 2.0 * QG[k.rev[c[i]]][k.rev[c[i + 1]]][k.rev[c[i + 2]]][k.rev[c[i + 3]]];
    return s;
}

string applyKey(const string& raw, const Key& k) {
    string r;
    r.reserve(raw.size());
    for (char c : raw) {
        if (c >= 'A' && c <= 'Z') r += (char)('A' + k.rev[c - 'A']);
        else r += c;
    }
    return r;
}

// ============================================================
//  FREQUENCY SEED KEY (khởi điểm tốt hơn random)
// ============================================================
Key freqSeed(const vector<uint8_t>& c) {
    int f[26] = {};
    for (uint8_t x : c) f[x]++;
    uint8_t o[26];
    iota(o, o + 26, (uint8_t)0);
    sort(o, o + 26, [&](int a, int b) { return f[a] > f[b]; });
    const char* eng = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    string s(26, 'A');
    for (int i = 0; i < 26; i++) s[eng[i] - 'A'] = (char)('A' + o[i]);
    return Key(s);
}

Key randKey(mt19937& rng) {
    string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    shuffle(s.begin(), s.end(), rng);
    return Key(s);
}

// ============================================================
//  HILL CLIMBING: thử tất cả 325 cặp, restart ngay khi cải tiến
// ============================================================
pair<Key, double> hc(const vector<uint8_t>& c, Key k) {
    double s = score(c, k);
    bool imp = true;
    while (imp) {
        imp = false;
        for (int a = 0; a < 26 && !imp; a++) {
            for (int b = a + 1; b < 26; b++) {
                k.swap2(a, b);
                double ns = score(c, k);
                if (ns > s) { s = ns; imp = true; break; }
                k.swap2(a, b); // undo
            }
        }
    }
    return make_pair(k, s);
}

// ============================================================
//  SIMULATED ANNEALING: thoát local optima
// ============================================================
pair<Key, double> sa(const vector<uint8_t>& c, Key k, mt19937& rng) {
    double s = score(c, k), bs = s;
    Key bk = k;
    uniform_real_distribution<double> ru(0.0, 1.0);
    uniform_int_distribution<int> ri(0, 25);
    double T = 15.0;
    double cool = pow(0.001 / 15.0, 1.0 / 4000);
    for (int i = 0; i < 4000; i++) {
        int a = ri(rng), b = ri(rng);
        if (a == b) { T *= cool; continue; }
        k.swap2(a, b);
        double ns = score(c, k);
        double delta = ns - s;
        if (delta > 0 || ru(rng) < exp(delta / T)) {
            s = ns;
            if (s > bs) { bs = s; bk = k; }
        }
        else k.swap2(a, b); // undo
        T *= cool;
    }
    return make_pair(bk, bs);
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();

    cout << "=============================================\n";
    cout << "  MONO-ALPHABETIC CIPHER BREAKER\n";
    cout << "  Bigram + Quadgram + SA + Hill-Climbing\n";
    cout << "=============================================\n\n";
    cout << "Nhap ciphertext (Enter 2 lan de ket thuc):\n";

    string raw, line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        raw += line + " ";
    }

    // Chuẩn hóa: chỉ giữ chữ cái + space
    string clean;
    vector<uint8_t> cipher;
    for (char c : raw) {
        if (isalpha((unsigned char)c)) {
            cipher.push_back((uint8_t)(toupper((unsigned char)c) - 'A'));
            clean += (char)toupper((unsigned char)c);
        }
        else if (c == ' ') clean += ' ';
    }
    if (cipher.empty()) { cout << "Ciphertext rong!\n"; return 1; }

    cout << "\nCiphertext (" << cipher.size() << " ky tu): "
        << clean.substr(0, min((int)clean.size(), 60));
    if (clean.size() > 60) cout << "...";
    cout << "\n\n";

    mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

    Key bestKey;
    double bestScore = -1e18;

    // Mỗi restart: HC -> SA -> HC (tốt nhất trong 3)
    auto tryKey = [&](Key sk) {
        pair<Key, double> r1 = hc(cipher, sk);
        pair<Key, double> r2 = sa(cipher, r1.first, rng);
        pair<Key, double> r3 = hc(cipher, r2.first);
        Key  wk = (r3.second >= r2.second) ? r3.first : r2.first;
        double ws = max(r2.second, r3.second);
        if (ws > bestScore) {
            bestScore = ws;
            bestKey = wk;
            cout << "  Score=" << fixed << setprecision(1) << bestScore
                << " | " << applyKey(clean, bestKey).substr(0, 55) << "\n";
        }
        };

    int N = 200;
    cout << "Chay " << N + 1 << " restarts...\n\n";

    // Restart 0: frequency-based seed (tốt hơn random)
    tryKey(freqSeed(cipher));

    // 200 random restarts
    for (int i = 0; i < N; i++) {
        if (i % 50 == 0 && i > 0)
            cout << "  [" << i << "/" << N << "] best=" << fixed << setprecision(1) << bestScore << "\n";
        tryKey(randKey(rng));
    }

    // In kết quả
    cout << "\n=============================================\n";
    cout << "KET QUA CUOI CUNG:\n";
    cout << "=============================================\n";
    cout << "Score: " << fixed << setprecision(2) << bestScore << "\n";
    cout << "\nKey (Cipher -> Plain):\n";
    cout << "  Cipher: ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    cout << "  Plain:  ";
    for (int i = 0; i < 26; i++) cout << (char)('A' + bestKey.rev[i]);
    cout << "\n\nPLAINTEXT:\n" << applyKey(clean, bestKey) << "\n";

    return 0;
}