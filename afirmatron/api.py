import logging
import os
import hashlib
from flask import (
    Blueprint, request, Response, send_from_directory,
    make_response
)

from afirmatron import File 
from afirmatron.version import should_update

BIN_DIR='/Users/trevorgrayson/projects/esp8266/ota/server/static'

routes = Blueprint('afirmatron', __name__)
logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)

@routes.route('/update')
def update():
    logger.info(request.headers)
    if should_update(version=0):
        # filename=os.path.join(BIN_DIR, 'ota.ino.bin')
        binary = File.from_filename(HTTP_X_ESP8266_STA_MAC=request.headers.get('X-Esp8266-Sta-Mac'))
        return make_response(send_from_directory(BIN_DIR, binary.filename),
                             200, response_headers(binary))

    return 'current', 305
    

@routes.route('/update/<string:device_name>', methods=["POST"])
def upload(device_name):
    octet = request.get_data()
    File.save(device_name, octet)
    return 'ok', 201

def response_headers(binary):
    filebody = open(BIN_DIR + "/" + binary.filename, 'rb').read()
    headers = {
        # 'HTTP 200 OK'
        'Content-Type': 'application/octet-stream',
        'Content-Disposition': 'attachment; filename={}'.format(binary.filename),
        'Content-Length': binary.length,
        'x-MD5': hashlib.md5(binary.octet).hexdigest()
    }
    logger.info(headers)
    return headers

# [HTTP_USER_AGENT] => ESP8266-http-Update
# [HTTP_X_ESP8266_STA_MAC] => 18:FE:AA:AA:AA:AA
# [HTTP_X_ESP8266_AP_MAC] => 1A:FE:AA:AA:AA:AA
# [HTTP_X_ESP8266_FREE_SPACE] => 671744
# [HTTP_X_ESP8266_SKETCH_SIZE] => 373940
# [HTTP_X_ESP8266_SKETCH_MD5] => a56f8ef78a0bebd812f62067daf1408a
# [HTTP_X_ESP8266_CHIP_SIZE] => 4194304
# [HTTP_X_ESP8266_SDK_VERSION] => 1.3.0
# [HTTP_X_ESP8266_VERSION] => DOOR-7-g14f53a19

