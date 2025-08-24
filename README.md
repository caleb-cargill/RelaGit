# RelaGit
I find myself using the command line more and more as I progress through my career. As I grow in familiarity with it, I find it to be much more efficient than navigating any user interface. However, there are still times when I need to accomplish something, and do not know the command, either because I have never been faced with such a situation, or it is a sitatuation I do not run into frequently. Therefore I came up with RelaGit (or *relational git*). 

The intent is fairly simple: to be able to learn new commands while in the context of a terminal, rather than having to navigate to some search engine or documentation to figure it out. RelaGit utilizes the *llama3* model running locally through *Ollama*. A request is made through the command line, the prompt is cleaned up and passed to *llama3*, and the model's response is processed and output to the user as a sequence of commands to run. 

*Note on the name*: I originally was thinking of limiting functionality to git commands, but ended up modifying the prompts to be inclusive of all command line commands. This felt more useful, but also added complexity. 

# Dependencies
- Ollama, running llama3
- nlohmann_json (managed with cmake)
- libcurl (managed with cmake)

# Further Development
This has been a fun project to work on, but it is a bit short of an MVP. The following work needs to occur:
- Option to run the commands after they are provided
- Validation and consistency of model responses (bug identified so far: the same request made multiple times in a row and a different, often incorrect response returned)
- Add context and chat history (in chat mode in particular)
- System/environment awareness
- Optional explanations and clean-up of output for better user experience