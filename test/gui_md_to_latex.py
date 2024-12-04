import tkinter as tk
from tkinter import scrolledtext
from mistletoe import markdown
from mistletoe.latex_renderer import LaTeXRenderer
import pyperclip

def transform_to_latex():
    """Transforms the input text into LaTeX format."""
    input_text = input_textarea.get("1.0", tk.END).strip()
    input_text = input_text.replace('\\(','\\\\(')
    input_text = input_text.replace('\\)','\\\\)')
    print(input_text)
    if input_text:
        latex_text = markdown(input_text, LaTeXRenderer)
        latex_text = latex_text.replace('\\hrulefill','\n\\hrulefill')
        

        output_textarea.config(state=tk.NORMAL)
        output_textarea.delete("1.0", tk.END)
        output_textarea.insert(tk.END, latex_text)
        output_textarea.config(state=tk.DISABLED)

def copy_output():
    """Copies the output LaTeX text to the clipboard."""
    output_text = output_textarea.get("1.0", tk.END).strip()
    if output_text:
        pyperclip.copy(output_text)

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
transform_button = tk.Button(root, text="Transform to LaTeX", command=transform_to_latex, state=tk.DISABLED)
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
