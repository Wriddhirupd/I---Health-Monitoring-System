# -- coding: utf-8 --
"""
@author: Wriddhirup Dutta
"""

import urllib
import requests
import json
import time

READ_API_KEY='xxxxxxxxxxxxxxxx'
CHANNEL_ID='xxxxxx'

while True:
    TS = urllib.request.urlopen("http://api.thingspeak.com/channels/%s/feeds/last.json?api_key=%s" \
                       % (CHANNEL_ID,READ_API_KEY))

    response = TS.read()
    data=json.loads(response)


    a = str(data['created_at'])
    b = str(data['field1'])
    c = str(data['field2'])
    d = str(data['entry_id'])
    print (a + "    " + b + "    " + c +"     " + d)
    time.sleep(5)   

    TS.close()
