#include "checkerror.h"

CheckError::CheckError()
{

}
bool CheckError::CheckKeyError(QString key)
{
    return key.size();
    for(int i=0;i<key.size();i++)
    {
        if(!((key[i]<='9'&&key[i]>='0')||(key[i]>='a'&&key[i]<='z')||(key[i]>='A'&&key[i]<='Z')))
            return false;
    }
    return true;
}
