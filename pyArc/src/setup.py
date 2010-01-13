# -*- coding: utf-8 -*-

from distutils.core import setup, Extension

ARCCdir = '../../ARCC/'

setup (name = 'ArcC',
       version = '1.0 Aplha',
       description = 'The ArcLib C API',
       author = 'Clay Smith',
       author_email = 'clay.smith.r@gmail.com',
       url = 'http://docs.python.org/extending/building',
       long_description = '''
ArcC API
''', 
	packages=['pyArc'],
	py_modules=['ArcC'],
	ext_modules = [Extension('_ArcC',
    include_dirs = ['/usr/include', '/usr/include/freetype2', ARCCdir],
    libraries = ['GL', 'SDL', 'log4c'],
    library_dirs = ['/usr/lib'],
    sources = ['swig.i', ARCCdir + 'Window.c', ARCCdir + 'Log.c', ARCCdir + 'Font.c'],
    swig_opts=['-I' + ARCCdir]
                    )])
