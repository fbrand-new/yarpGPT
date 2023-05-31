import yarp
import os
import sys
import openai

import apiconf

class GPTCallback(yarp.BottleCallback):
    def __init__(self,initial_prompt,system_context="",model="gpt-3.5-turbo"):
        self.context = system_context
        self.initial_prompt = initial_prompt
        self.model = model
        self.response_port = yarp.BufferedPortBottle()
        self.response_port.open("/yarpGPT/target:o")
        super().__init__()

    def onRead(self,bottle,reader):
        messages = self.create_messages(bottle)
        response = self.answer(messages)
        self.write_response(response)

    def answer(self,messages):
        
        response = openai.ChatCompletion.create(
            model=self.model,
            messages=messages
        )

        return response
    
    def create_messages(self,bottle):
        
        messages = []

        # We suppose that context is a single string
        if self.context:
            messages.append({"role": "system", "content": self.context})
        if self.initial_prompt:
            messages.append({"role": "user", "content": self.initial_prompt})

        # We take the input from the input bottle.
        # bottle = ("My prompt")
        prompt = bottle.toString()

        messages.append({"role": "user", "content": prompt})

        #TODO: 
        #We need to save the responses and append it back to the messages, keeping an internal state of the conversation. For now it will be "stateless"

        return messages

    def write_response(self,response):
        answer = response['choices'][0]['message']['answer']
        bottle = self.response_port.prepare()
        bottle.addString(answer)
        self.response_port.write()


class yarpGPT(yarp.RFModule):

    def configure(self,rf):

        yarp.Network.init()
        self.period = 0.2
        self.system_context = rf.find("system_context").asString()
        self.initial_prompt_file = rf.find("initial_prompt_file").asString()

        with open(self.initial_prompt_file, 'r') as file:
            self.initial_prompt = file.read().rstrip()

        self.api_conf = rf.find("apiconf").asString()
        if self.api_conf == "OpenAI":
            apiconf.OpenAIConf()
        if self.api_conf == "Azure":
            apiconf.AzureConf()

        self.in_port = yarp.BufferedPortBottle()
        self.in_port.open("/yarpGPT/text:i")

        # callback = GPTCallback(self.system_context,self.initial_prompt)
        # self.in_port.useCallback(callback)
        
        return True
    
    def updateModule(self):

        message = yarp.Bottle()

        if(self.in_port.read(message)):
            