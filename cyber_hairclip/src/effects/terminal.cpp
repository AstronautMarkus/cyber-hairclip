#include "effects.h"

// A hacking session typed live: recon, brute force, root, cover your tracks. '\x01' renders as 白.
void fxTerminal(uint32_t t) {
  static const char *const S[] = {
    "$ whoami", "guest",
    "$ nmap -sS 10.0.0.7", "22/tcp open  ssh", "80/tcp open  http",
    "$ hydra 10.0.0.7 ssh", "[22] root:Shiro (\x01)",
    "$ ssh root@10.0.0.7", "# id", "uid=0(root) gid=0",
    "# cat /etc/shadow", "root:$6$x9f2:19337",
    "# history -c", "# exit", ">> HACK THE PLANET <<"};
  const int N = sizeof(S) / sizeof(S[0]), CH = 40, PAUSE = 220;  // ms per keystroke, pause after each line
  int l = 0, n = 0;
  for (uint32_t acc = 0; l < N; l++) {  // which line is being typed and how many chars so far
    int len = strlen(S[l]);
    bool cmd = S[l][0] == '$' || S[l][0] == '#';
    uint32_t d = (cmd ? (len - 2) * CH : 0) + PAUSE;
    if (t < acc + d) { n = cmd ? min(len, 2 + (int)(t - acc) / CH) : len; break; }
    acc += d;
  }
  if (l == N) { l = N - 1; n = strlen(S[l]); }
  int first = max(0, l - 7);  // 8 visible rows: old lines scroll off the top
  for (int i = first; i <= l; i++) {
    display.setCursor(0, (i - first) * 8);
    if (i == N - 1) display.setTextColor(BLACK, WHITE);
    for (int k = 0, e = i == l ? n : strlen(S[i]); k < e; k++)
      if (S[i][k] == '\x01') printKanjiShiro(1, WHITE, BLACK);
      else display.print(S[i][k]);
  }
  display.setTextColor(WHITE);
  if ((t >> 8) & 1) display.fillRect(display.getCursorX() + 1, display.getCursorY(), 5, 8, WHITE);
}
