import yarp
import os
import sys
import openai
import itertools

from apiconf import OpenAIConf, AzureConf

class GPTCore():

    def __init__(self,
                 system_message="",
                 user_messages=[],
                 assistant_messages=[],
                 model="gpt-3.5-turbo") -> None:
        self.system_message = system_message
        self.model = model
        self.user_messages = user_messages
        self.assistant_messages = assistant_messages

    def create_messages(self,bottle) -> list:
        
        messages = []

        # We suppose that context is a single string
        if self.system_message:
            messages.append({"role": "system", "content": self.system_message})        

        # bottle = ("My prompt")
        prompt = bottle.toString()

        # We take the input from the input bottle.
        # We want to alternate between user and assistant
        if len(self.user_messages) == len(self.assistant_messages):
            self.user_messages.append(prompt)
        else:
            #Append prompt to system context given as user message
            #This technique is important for gpt-3.5-turbo as highlighted
            #in https://platform.openai.com/docs/guides/chat/introduction
            self.user_messages[-1] = self.user_messages[-1] + " " + prompt

        # We alternate between user and assistant messages
        iter = itertools.zip_longest(self.user_messages,self.assistant_messages,fillvalue=None)

        for user_mex, assistant_mex in iter:
            if user_mex:
                messages.append({"role":"user","content": user_mex})
            if assistant_mex:
                messages.append({"role":"assistant","content":assistant_mex})

        print(messages)

        return messages

    def answer(self,messages):

        print("Answering ...")

        response = openai.ChatCompletion.create(
            model=self.model,
            messages=messages
        )


        # response =  {
        #     'id' : '123',
        #     'choices' : [
        #         {
        #             'message' : {
        #                 'role' : 'assistant',
        #                 'answer' : "I am dumb, I don't know how to answer" 
        #             },
        #             'finish_reason' : 'stop',
        #             'index' : 0
        #         }
        #     ]
        # }

        return response

    def create_response(self,response) -> yarp.Bottle:
        answer = response['choices'][0]['message']['answer']
        self.assistant_messages.append(answer)
        bottle = yarp.Bottle()
        bottle.addString(answer)
        return bottle

class yarpGPT(yarp.RFModule):

    def configure(self,rf):

        yarp.Network.init()

        #Default values 
        self.initial_prompt = None
        self.period = 0.2

        #Read configuration from resource finder 
        self.delay = rf.find("delay").asFloat32()
        self.system_context = rf.find("system_context").asString()
        self.initial_prompt_file = rf.find("initial_prompt_file").asString()

        if self.initial_prompt_file:
            with open(self.initial_prompt_file, 'r') as file:
                self.initial_prompt = file.read().rstrip()

        self.api_conf = rf.find("apiconf").asString()

        if self.api_conf == "OpenAI":
            OpenAIConf()
        if self.api_conf == "Azure":
            AzureConf()

        self.in_port = yarp.RpcServer()
        self.in_port.open("/yarpGPT/text:i")

        if self.initial_prompt:
            self.core = GPTCore(self.system_context,[self.initial_prompt])
        else:
            self.core = GPTCore(self.system_context)

        return True
    
    def updateModule(self):

        prompt = yarp.Bottle()
        if(self.in_port.read(prompt,True)):    
            print(prompt.toString())
            #Format input, ask chat-gpt and format output
            messages = self.core.create_messages(prompt)
            api_answer = self.core.answer(messages)
            answer = self.core.create_response(api_answer)
            
            #Reply to rpc 
            self.in_port.reply(answer)

            #Wait t seconds before having the api available again
            yarp.delay(self.delay)

        return True
    
    def getPeriod(self) -> float:
        return self.period
    
    def interruptModule(self):
        self.in_port.interrupt()
        return True
    
    def cleanup(self):
        self.in_port.close()
        return True