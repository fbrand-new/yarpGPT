import unittest
import os
import yarp
from yarpGPT.api import GPTCallback
from unittest.mock import MagicMock

current_path = os.path.dirname(__file__)



class APIInputTest(unittest.TestCase):

    def test_api_input(self):
        yarp.Network.init()
        # yarp.Network.setLocalMode(True)
        context = ""
        port = yarp.BufferedPortBottle()
        out_port = yarp.BufferedPortBottle()
        out_port_name = "/yarpGPT/target:i"
        out_port.open(out_port_name)
        # out_bottle = yarp.Bottle() 

        fake_key = "fake_key"
        callback = GPTCallback(fake_key,context)

        mock_answer = {
            'id' : '123',
            'choices' : [
                {
                    'message' : {
                        'role' : 'assistant',
                        'answer' : 'Hello world!'
                    },
                    'finish_reason' : 'stop',
                    'index' : 0
                }
            ]
        }
        callback.answer = MagicMock(return_value=mock_answer)

        port.useCallback(callback)
        port.open("/test/text:i")

        p2 = yarp.BufferedPortBottle()
        p2.open("/test/text:o")
        input_bottle = p2.prepare()
        input_bottle.addString("Ask me anything")
        self.assertTrue(yarp.Network.connect(p2.getName(),port.getName()))
        self.assertTrue(yarp.Network.connect("/yarpGPT/target:o","/yarpGPT/target:i"))
        print("After second connection")
        yarp.delay(1)
        p2.write()
        print("After p2 write")
        out_bottle = out_port.read()
        print("After second read")
        self.assertEqual(out_bottle.toString().strip('\"'),mock_answer['choices'][0]['message']['answer'])


