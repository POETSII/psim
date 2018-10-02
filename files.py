import json

def read_json(file):
    """Read a JSON file."""
    with open(file, "r") as fid:
        return json.load(fid)


def read_file(file):
    """Return file content as a string."""
    with open(file, "r") as fid:
        return fid.read()


def write_file(file, content):
    """Write string to file."""
    with open(file, "w") as fid:
        fid.write(content)
