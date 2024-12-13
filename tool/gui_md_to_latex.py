import tkinter as tk
from tkinter import scrolledtext
from mistletoe import markdown
from mistletoe.latex_renderer import LaTeXRenderer
import pyperclip
import re


def transform_to_latex():
    """Transforms the input text into LaTeX format."""
    input_text = input_textarea.get("1.0", tk.END).strip()

    if input_text:
        input_text = (
            # in math expressions, the backslash "\"
            # in "\[ ... \]" and "\( ... \)" are necessary to retain
            input_text.replace("\\[", "\\\\[")
            .replace("\\]", "\\\\]")
            .replace("\\(", "\\\\(")
            .replace("\\)", "\\\\)")
        )
        latex_text = markdown(input_text, LaTeXRenderer)
        latex_text = (
            # in math expressions, the "{" and "}" do not need to be escaped.
            latex_text.replace("\\hrulefill", "\n\\hrulefill")
            .replace("\\{", "{")
            .replace("\\}", "}")
            # the "_" in math expressions does not need to be escaped.
            # The effect of replace "\_" to "_" can be reflected in this example:
            # \lim\_{x\to \infty} -> \lim_{x\to \infty}
            .replace("\\_", "_")
        )

        pattern = r"\d+\.\s\\textbf\{(.*?)\}"
        # pattern = r"\\textbf\{(.*?)\}"
        # final_lines = [re.sub(pattern, r"\1", line) for line in main_lines]
        # final_text = '\n'.join(final_lines)

        output_textarea.config(state=tk.NORMAL)
        output_textarea.delete("1.0", tk.END)
        output_textarea.insert(tk.END, re.sub(pattern, r"\1", latex_text))
        output_textarea.config(state=tk.DISABLED)


def copy_output():
    """Copies the output LaTeX text to the clipboard."""
    output_text = output_textarea.get("1.0", tk.END).strip()
    if output_text:
        # remove these lines:
        # \documentclass{article}
        # \usepackage{ ... }
        # \begin{document}
        # \end{document}
        lines = output_text.splitlines()
        cut_text_from = 0
        for i, line in enumerate(lines):
            if "\\begin{document}" in line:
                cut_text_from = i
                break
        main_lines = lines[
            cut_text_from + 2 : -1
        ]  # there is a new-line below \begin{document}, so +2
        text = "\n".join(main_lines)
        pyperclip.copy(text)


def update_transform_button_state(*args):
    """Enables or disables the transform button based on input area content."""
    if input_textarea.get("1.0", tk.END).strip():
        transform_button.config(state=tk.NORMAL)
    else:
        transform_button.config(state=tk.DISABLED)


# Create the main Tkinter window
root = tk.Tk()
root.title("Markdown to LaTeX Transformer")
root.geometry("800x600")  # Set the initial size of the window

# Configure grid weights for resizing
root.grid_columnconfigure(0, weight=1)
root.grid_columnconfigure(1, weight=0)
root.grid_rowconfigure(1, weight=1)
root.grid_rowconfigure(2, weight=1)

# Transform Button
transform_button = tk.Button(
    root, text="Transform to LaTeX", command=transform_to_latex, state=tk.DISABLED
)
transform_button.grid(row=0, column=0, padx=5, pady=5, sticky="w")

# Copy Button
copy_button = tk.Button(root, text="Copy Output", command=copy_output)
copy_button.grid(row=0, column=1, padx=5, pady=5, sticky="w")

# Input Text Area
input_textarea = scrolledtext.ScrolledText(root, height=10)
input_textarea.grid(row=1, column=0, columnspan=2, padx=5, pady=5, sticky="nsew")
input_textarea.bind("<<Modified>>", update_transform_button_state)

# Output Text Area
output_textarea = scrolledtext.ScrolledText(root, height=10, state=tk.DISABLED)
output_textarea.grid(row=2, column=0, columnspan=2, padx=5, pady=5, sticky="nsew")

# Run the Tkinter event loop
root.mainloop()
