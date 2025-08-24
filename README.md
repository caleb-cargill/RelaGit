# RelaGit
I find myself using the command line more and more as I progress through my career. As I grow in familiarity with it, I find it to be much more efficient than navigating any user interface. However, there are still times when I need to accomplish something, and do not know the command, either because I have never been faced with such a situation, or it is a sitatuation I do not run into frequently. Therefore I came up with RelaGit (or *relational git*). 

The intent is fairly simple: to be able to learn new commands while in the context of a terminal, rather than having to navigate to some search engine or documentation to figure it out. RelaGit utilizes the `codellama` model running locally through *Ollama*. A request is made through the command line, the prompt is cleaned up and passed to *codellama*, and the model's response is processed and output to the user as a sequence of commands to run. 

*Note on the name*: I originally was thinking of limiting functionality to git commands, but ended up modifying the prompts to be inclusive of all command line commands. This felt more useful, but also added complexity. 

# Dependencies
- Ollama, running codellama
- nlohmann_json (managed with cmake)
- libcurl (managed with cmake)