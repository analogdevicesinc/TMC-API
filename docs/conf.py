import subprocess, sys, os

def run_doxygen(folder):
    """Run the doxygen make command in the designated folder"""

    try:
        retcode = subprocess.call("cd %s; make" % folder, shell=True)
        if retcode < 0:
            sys.stderr.write("doxygen terminated by signal %s" % (-retcode))
    except OSError as e:
        sys.stderr.write("doxygen execution failed: %s" % e)


def generate_doxygen_xml(app):
    """Run the doxygen make commands if we're on the ReadTheDocs server"""

    read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

    if read_the_docs_build:

        #run_doxygen("../tmc/test")
        run_doxygen("../tmc/ic/tmc2300")
        #run_doxygen("../tmc/helpers")


def setup(app):

    # Add hook for building doxygen xml when needed
    app.connect("builder-inited", generate_doxygen_xml)

extensions = [ 
    'breathe', 
    'sphinx_rtd_theme' 
]

breathe_default_project = "TMC2300"

breathe_projects = {
    # "TMC-API": "_build/doxygen/xml",
    "TMC2300": "_build/doxygen/TMC2300/xml",
    "TMC2240": "_build/doxygen/TMC2240/xml"
}

breathe_projects_source = {
    "TMC2300" : ( "../tmc/ic/TMC2300", [ "TMC2300.h", "TMC2300.c", "TMC2300_Constants.h", "TMC2300_Fields.h", "TMC2300_Register.h" ]),
    "TMC2240" : ( "../tmc/ic/TMC2240", [ "TMC2240.h", "TMC2240.c","TMC2240_Constants.h", "TMC2240_Fields.h", "TMC2240_Register.h" ])
}

breathe_implementation_filename_extensions = ['.c', '.cpp']

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

html_theme = "sphinx_rtd_theme"
html_static_path = ['_static']
