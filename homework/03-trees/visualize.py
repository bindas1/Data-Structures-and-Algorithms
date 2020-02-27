import os

import click
import jinja2


OUTPUT_DIR = 'images'
FRAME_SUBDIR = 'frames'


class InputError(Exception):
    pass


class Node:
    def __init__(key, left = None, right = None):
        self.key = key
        self.left = left
        self.right = right


@click.command()
@click.argument('filename')
def parse_input(filename):
    """Generate a sequence of binary tree visualizations from FILENAME.

    FILENAME should contain a description of a binary tree in an array format, one step per line.
    
    Each line consists of a number of nodes (integers) separated by whitespace characters.
    Node [i] has children at [2*i + 1] and [2*i + 2]. Empty nodes are designated by `--`.

    \b
                40 
              /    \\
             /      \\
            /        \\
          20          60
         /  \        /  \\
        /    \      /    \\
       10    --    50    --
    
    should be written down as:

    \b
    >>> with open('tree.bt', 'r') as input_file:
    >>>     print(input_file.read())
    40 20 60 10 -- 50 --

    This script requires a working XeLaTeX installation.

    """
    
    files = []

    with open(filename, 'r') as input_file:
        lines = input_file.read().splitlines()

        for line_idx, line in enumerate(lines):
            nodes = line.split()
            for node_idx, node in enumerate(nodes):
                if not is_node_valid(node): raise InputError(f"In line {line_idx}, node {node_idx}: {node}")
                if node != '--':
                    node = int(node)
            
            if not len(nodes):
                raise InputError(f"No nodes found in the input file (line {line_idx}).")
            
            if nodes[0] == '--':
                raise InputError(f'Root node cannot be empty (line {line_idx}).') 

            if len(nodes) > 15:
                raise InputError(f"Default images settings do not allow for trees with more than 15 nodes (line {line_idx}).")

            base = os.path.splitext(filename)[0]
            output_filename = f'{OUTPUT_DIR}/{FRAME_SUBDIR}/{base}-{line_idx:02d}.tex'
            files.append(f'{FRAME_SUBDIR}/{base}-{line_idx:02d}.pdf')
            
            with open(output_filename, 'w') as output_file:
                content = render_tree(create_node(nodes, 0))
                output_file.write(content)

        merger_filename = f'{OUTPUT_DIR}/{base}.tex'
        
        with open(merger_filename, 'w') as merger_file:
            content = render_merger(files)
            merger_file.write(content)


def is_node_valid(node):
    if node == '--':
        return True
    return node.isdecimal() and 0 < int(node) < 200


def create_node(nodes, idx):
    left_idx = 2 * idx + 1
    right_idx = 2 * idx + 2

    children = []
    if left_idx < len(nodes):
        children.append(create_node(nodes, left_idx))
    if right_idx < len(nodes):
        children.append(create_node(nodes, right_idx))

    if len(children) == 1:
        nullptr = { 'key': '--', 'children': []}
        children.append(nullptr)
        
    return {'key': nodes[idx], 'children': children}
 

def render_tree(tree):
    with open('latex.jinja2', 'r') as latex_template:
        template = latex_template.read()
    
    t = jinja2.Template(template)

    return t.render({'root': tree})


def render_merger(files):
    with open('merger.jinja2', 'r') as merger_template:
        template = merger_template.read()
    
    t = jinja2.Template(template)

    return t.render({'files': files})


if __name__ == "__main__":
    parse_input()
