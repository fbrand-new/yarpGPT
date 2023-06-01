import unittest
import os
import yarp
from yarpGPT.api import GPTCore
from unittest.mock import MagicMock

current_path = os.path.dirname(__file__)

class APICoreTest(unittest.TestCase):

    def test_create_message(self):

        #Context for the api
        initial_prompt = "Your mother should know"
        context = "You are a walrus!"

        #Prompt for the api
        input = yarp.Bottle()
        prompt = "Wake up honey"
        input.addString(prompt)

        #Create utils object and get api_input
        gptcore = GPTCore(initial_prompt,context)
        api_input = gptcore.create_messages(input)

        #Check that the first message is a system one, and gives the context
        self.assertEqual(api_input[0]["role"],"system")
        self.assertEqual(api_input[0]["content"],context)

        #Check that the second message is the initial prompt
        self.assertEqual(api_input[1]["role"],"user")
        self.assertEqual(api_input[1]["content"],initial_prompt)

        #Check that the third message is the prompt
        self.assertEqual(api_input[2]["role"],"user")
        self.assertEqual(api_input[2]["content"],prompt)

    def test_create_response(self):

        #Create utils object and get api_input
        gptcore = GPTCore("")

        #Create a fake answer
        answer = 'Hello world!'
        mock_answer = {
            'id' : '123',
            'choices' : [
                {
                    'message' : {
                        'role' : 'assistant',
                        'answer' : answer 
                    },
                    'finish_reason' : 'stop',
                    'index' : 0
                }
            ]
        }

        #Extract the information we care about from the api like answer
        actual_answer = gptcore.create_response(mock_answer)

        self.assertEqual(answer,actual_answer.toString().strip('\"'))
