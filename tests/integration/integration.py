import yarp
import unittest

class APITest(unittest.TestCase):

    def test_api_call(self):

        yarp.Network.init()

        # Opening an rpc client port and connecting to FakeDevice rpc

        yarp_gpt_rpc = yarp.RpcClient()
        yarp_gpt_rpc.open("/chat/test")
        _ = yarp.Network.connect(yarp_gpt_rpc.getName(),"/chat/rpc")

        prompt = yarp.Bottle()
        prompt.addString("ask")
        prompt.addString("Does the goo goo muck?")
        answer = yarp.Bottle()

        yarp_gpt_rpc.write(prompt,answer)

        expected_answer = "Fatti non foste per viver come bruti ma per seguir virtute e canoscenza"
        self.assertEqual(answer.toString().strip('/"'),expected_answer)