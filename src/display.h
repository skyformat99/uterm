#pragma once

#include <SkTypeface.h>
#include <SkCanvas.h>
#include <SkPaint.h>

#include "uterm.h"
#include "terminal.h"
#include "text.h"
#include "marker_set.h"

class Display {
public:
  Display(Terminal *term);

  void SetTextSize(int size);
  void SetPrimaryFont(string name);
  void SetFallbackFont(string name);

  void Resize(int width, int height);
  void Draw(SkCanvas *canvas);
private:
  void TermDraw(const u32string& str, Pos pos, Attr attr, int width);
  void UpdateWidth();
  void UpdatePositions();
  void UpdateGlyphs();
  void UpdateGlyph(int x, int y);
  void HighlightRange(SkCanvas *canvas, Pos begin, Pos end, SkColor color);

  Terminal *m_term;
  int m_char_width{-1};

  TextManager m_text;
  GlyphRenderer m_primary, m_fallback;
  SkPaint m_highlight_paint;
  std::vector<bool> m_fallbacks;

  using AttrSet = MarkerSet<Attr, Attr::Hash>;
  AttrSet m_attrs;
};