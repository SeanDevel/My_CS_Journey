import mistletoe
from mistletoe.latex_renderer import LaTeXRenderer

with open('markdown.md', 'r') as fin:
    rendered = mistletoe.markdown(fin, LaTeXRenderer)

print(rendered)