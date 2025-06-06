//Channel.cpp
#include "Channel.hpp"

// Constructeur par défaut + paramétré + copie + affectation + Destructeur 
Channel::Channel() : name(""), topic(""), inviteOnly(false), password(""), maxUsers(50)
{
}
Channel::Channel(const std::string& channelName, const std::string& channelPassword, int maxUsers)
    : name(channelName), topic(""), inviteOnly(false), password(channelPassword), maxUsers(maxUsers)
{
}
Channel::Channel(const Channel& other)
    : name(other.name), topic(other.topic), members(other.members),
      inviteOnly(other.inviteOnly),
      password(other.password), maxUsers(other.maxUsers)
{
}
Channel& Channel::operator=(const Channel& other)
{
    if (this != &other) 
    {
        name = other.name;
        topic = other.topic;
        members = other.members;
        inviteOnly = other.inviteOnly;
        password = other.password;
        maxUsers = other.maxUsers;

    }
    return *this;
}
Channel::~Channel()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-> Getters et setters --------------------------------------------------------------------------------------------------------------------------
std::string Channel::getName() const
{
    return name;
}
std::string Channel::getTopic() const
{
    return topic;
}
void Channel::setTopic(const std::string& newTopic)
{
    topic = newTopic;
}
int Channel::getOperatorCount() const 
{
    int count = 0;
    for (std::map<Client*, bool>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if (it->second)
            count++;
    }
    return count;
}
//-> Membres -----------------------------------------------------------------------------------------------------------------------------------
bool Channel::addMember(Client* client, bool isOp) 
{
    if (members.find(client) != members.end())
        return false;

    members.insert(std::make_pair(client, isOp));
    //members[client] = isOp;
    return true;
}
bool Channel::removeMember(Client* client) 
{
    return members.erase(client) > 0;
}
bool Channel::isEmpty() const 
{
    return members.empty();
}
bool Channel::isMember(Client* client) const 
{
    return members.find(client) != members.end();
}
bool Channel::isOperator(Client* client) const 
{
    std::map<Client*, bool>::const_iterator it = members.find(client);
    if (it != members.end())
        return it->second;
    return false;
}
void	Channel::sendAll(Client *cli, std::string& msg)
{
	std::string name = cli->getNickn();
	for (std::map<Client*, bool>::const_iterator it = members.begin(); it != members.end(); ++it) 
	{
		if (((it->first) != cli))
		{
			((it->first))->sendMessage(msg);
			((it->first))->prompt();
		}

	}
}

//-> Modes -------------------------------------------------------------------------------------------------------------------------------
/*
void Channel::setInviteOnly(bool isInviteOnly)
{
    this->inviteOnly = isInviteOnly;
}
void Channel::setTopicRestricted(bool isTopicRestricted)
{
    this->topicRestricted = isTopicRestricted;
}
void Channel::setKey(const std::string& key)
{   
    std::cout << " a faire " << std::endl;
}
void Channel::clearKey()
{
    std::cout << " a faire " << std::endl;
}
bool Channel::hasKey() const
{
    std::cout << " a faire " << std::endl;
}
void Channel::setUserLimit(int limit)
{
    std::cout << " a faire " << std::endl;
}
void Channel::clearUserLimit()
{
    std::cout << " a faire " << std::endl;
}
bool Channel::isFull() const
{
    std::cout << " a faire " << std::endl;
}
bool Channel::promoteToOperator(Client* client)
{
    std::map<Client*, bool>::iterator it = members.find(client);
    if (it != members.end()) 
    {
        it->second = true;
        return true;
    }
    return false;
}
bool Channel::demoteOperator(Client* client)
{
    std::map<Client*, bool>::iterator it = members.find(client);
    if (it != members.end()) 
    {
        it->second = false;
        return true;
    }
    return false;
}
*/


//-> Command -------------------------------------------------------------------------------------------------------------------------------
//std::string Channel::Topic_command(Client* client, const std::vector<std::string>& args) {}




//-> Utilitaires -------------------------------------------------------------------------------------------------------------------------------
void Channel::setPassword(const std::string& newPassword)
{
    this->password = newPassword;
}
bool Channel::checkPassword(const std::string& inputPassword) const
{
    return inputPassword == password;
}
int Channel::getMemberCount() const
{
    // Utilise size() dans <map> pour retourner le nombre de membre
    return members.size();
}
std::map<Client*, bool> Channel::getMembers()
{
    return this->members;
}
