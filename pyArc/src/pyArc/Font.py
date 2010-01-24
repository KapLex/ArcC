import ArcC

class Font:
    
    def __init__(self, fname, height):
        self.h = ArcC.ARC_Font()
        ArcC.ARC_FontInit(self.h, fname, height)
        
    def render(self, x,y, text, fmt, args):
        ArcC.ARC_FontRender(self.h, x,y, text, fmt, args)