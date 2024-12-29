#include <iostream>
#include <fstream>
#include <streambuf>

std::string readFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
        return "";  // return an empty string if file is not found

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

std::string handleHomePage()
{
    return readFile("public/index.html");
}

std::string handleDummyPage()
{
    return readFile("public/dummy.html");
}

std::string handleNotFound()
{
    return readFile("public/notfound.html");
}

std::string handleGreetRequest()
{
    return R"({"message": "Greetings from the server!"})";
}

std::string handlePostRequest()
{
    return R"({"message": "POST request received!", "status": "success"})";
}
