import yarp
import unittest

class APITest(unittest.TestCase):

    def test_api_call(self):

        yarp.Network.init()

        # Opening an rpc client port and connecting to yarpGPT rpc

        yarp_gpt_rpc = yarp.RpcClient()
        yarp_gpt_rpc.open("/yarpGPT/text:rpc")
        _ = yarp.Network.connect(yarp_gpt_rpc.getName(),"/yarpGPT/text:i")

        prompt = yarp.Bottle()
        prompt.addString("Does the goo goo muck?")
        answer = yarp.Bottle()

        yarp_gpt_rpc.write(prompt,answer)

        expected_answer = "The goo goo indeed mucks."
        self.assertEqual(answer.toString().strip('/"'),expected_answer)