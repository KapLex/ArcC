'''
Created on Jan 9, 2010

@author: clay
'''
import ArcC

class Window(object):
    '''
    classdocs
    '''

    def __init__(self, title="pyArc Application", width=800, height=600, isFS=False, isR=True):
        self.h = ArcC.Window()
        ArcC.ARC_OpenWindow(self.h, title, width, height, isFS, isR)
        '''
        Constructor
        '''
        
    def close(self):
        ArcC.ARC_Quit() 
        