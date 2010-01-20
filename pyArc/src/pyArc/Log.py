'''
Created on Jan 10, 2010

@author: clay
'''

import ArcC

class Log(object):
    '''
    classdocs
    '''

    def __init__(self, appender):
        ArcC.ARC_InitLogger(appender)
        '''
        Constructor
        '''
        
       