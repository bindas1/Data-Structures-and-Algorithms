ifdef OS
	CONVERT = magick
else
	CONVERT = convert
endif

PYTHON = python


.PHONY: all python latex merge_latex clean clean_latex thumbnails

all: thumbnails clean_latex

thumbnails:
	$(CONVERT) examples/dot/tree.png -resize 25% examples/dot/tree_th.png
	$(CONVERT) -density 300 examples/latex/tree.pdf -resize 50% examples/latex/tree.png

merge_latex: latex
	$(foreach file, $(wildcard images/*.tex), xelatex -output-directory=images ${file};)

latex: python
	$(foreach file, $(wildcard images/frames/*.tex), xelatex -output-directory=images/frames ${file};)
	
python: visualize.py tree.bt latex.jinja2 merger.jinja2
	$(PYTHON) visualize.py tree.bt

clean_latex: merge_latex latex
	rm -f images/*.aux images/*.log images/frames/*.aux images/frames/*.log

clean: clean_latex
	rm -f images/*.pdf