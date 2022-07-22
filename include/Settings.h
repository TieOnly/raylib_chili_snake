#pragma once
#include <fstream>
#include <sstream>

namespace settings
{
    inline constexpr int screenW = 800;
    inline constexpr int screenH = 600;
    inline constexpr int fps = 60;

    class Config
    {
    public:
        Config(std::string nameFile)
        {
            std::ifstream in( nameFile );
            std::string buf;
            if( in )
            {
                while(!in.eof())
                {
                    std::getline(in, buf);
                    if(buf == "[Tile Size]")
                    {
                        std::getline(in, buf);
                        dimension = std::stoi( buf );
                    } 
                    else if(buf == "[Board Size]")
                    {
                        std::getline(in, buf);
                        std::stringstream ss(buf);
                        std::string token;
                        
                        std::getline( ss, token, ' ' );
                        width = std::stoi( token );
                        std::getline( ss, token, ' ' );
                        height = std::stoi( token );
                    }
                    else if(buf == "[Speed Up]")
                    {
                        std::getline(in, buf);
                        speedUp = std::stof( buf );
                    }
                }
            }
        }
        int GetDimension() const {return dimension;}
        int GetWidth() const {return width;}
        int GetHeight() const {return height;}
        float GetSpeedUp() const {return speedUp;}
    private:
        std::string buf;
        int width = 20;
        int height = 20;
        int dimension = 10;
        float speedUp = 0.005f;
    };
}