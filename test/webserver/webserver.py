#!/usr/bin/env python3
import cherrypy
import json
import os
import time


class LedChannel:
    MODE_OFF = "Off"
    MODE_CONSTANT = "Constant"
    MODE_FADE = "Fade"
    MODE_FADE_ALTERNATE = "Alternating Fade"
    SUPPORTED_MODES = [MODE_OFF, MODE_CONSTANT, MODE_FADE, MODE_FADE_ALTERNATE]
    def __init__(self, channelNumber):
        self._channelNumber = channelNumber
        self._mode = LedChannel.MODE_CONSTANT
    @property
    def number(self):
        return self._channelNumber
    @property
    def mode(self):
        return self._mode
    def setMode(self, mode):
        assert mode in LedChannel.SUPPORTED_MODES
        self._mode = mode

class Root(object):
    def __init__(self):
        self._channels = [ LedChannel(1), LedChannel(2) ] 

    @cherrypy.expose
    @cherrypy.tools.allow(methods=['GET'])
    def index(self):
        with open('../../html/index.html', 'rt') as webpage:
            return webpage.read()

    @cherrypy.expose
    @cherrypy.tools.allow(methods=['GET'])
    def supported_modes(self, channel=None, mode=None):
        return json.dumps(LedChannel.SUPPORTED_MODES)

    @cherrypy.expose
    @cherrypy.tools.allow(methods=['GET'])
    def channels(self):
        channelList = []
        for channel in self._channels:
            channelList.append(channel.number)
        return json.dumps(channelList)

    @cherrypy.expose
    @cherrypy.tools.allow(methods=['GET', 'POST'])
    def mode(self, channel, mode=None):
        if cherrypy.request.method == 'POST':
            if mode is None:
                raise cherrypy.HTTPError(status=400, message='"mode" argument is required for method POST')
            ledChannel = self._getChannel(channel)
            newMode = self._validateMode(mode)
            ledChannel.setMode(newMode)
            return 'OK'
        elif cherrypy.request.method == 'GET':
            if mode is not None:
                raise cherrypy.HTTPError(status=400, message='"mode" argument not valid for method GET')
            ledChannel = self._getChannel(channel)
            print(f'Channel {channel} mode: {ledChannel.mode}')
            return ledChannel.mode
        else:
            raise cherrypy.HTTPError(status=405, message='Method %s not supported' % cherrypy.request.method)

    def _getChannel(self, channel):
        channelNumber = int(channel)
        for ledChannel in self._channels:
            if channelNumber == ledChannel.number:
                return ledChannel
        raise cherrypy.HTTPError(status=404, message=f'Channel {channel} not found')

    def _validateMode(self, requestedMode):
        for mode in LedChannel.SUPPORTED_MODES:
            if mode.lower() == requestedMode.lower():
                return mode
        raise cherrypy.HTTPError(status=400, message=f'{requestedMode} is not a valid mode. Must be one of {LedChannel.SUPPORTED_MODES}')

    

if __name__ == "__main__":
    conf = {
        '/': {
            'tools.staticdir.on': True,
            'tools.staticdir.dir': os.path.abspath('../../html/')
        }
    }

    cherrypy.config.update({'server.socket_port': 8081})
    cherrypy.server.socket_host = '0.0.0.0'
    cherrypy.quickstart(Root(), '/', conf)
    # conf = {
    #     '/': {
    #         'tools.staticdir.on': True,
    #         'tools.staticdir.dir': os.path.abspath('../../html/')
    #     },
    #     '/': {
    #         'tools.sessions.on': True
    #     }
    # }
    # cherrypy.config.update({'server.socket_port': 8081})
    # cherrypy.server.socket_host = '0.0.0.0'
    # cherrypy.quickstart(Root(), '/', conf)
