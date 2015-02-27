#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include<vector>
using namespace std;
int MAX_GUYS = 45;
int MAX_BULLETS=100;
SDL_Window* displayWindow;

/*
class SpaceInvader {
public:
    SpaceInvader();
    void Init();
    ~SpaceInvader() {
        SDL_Quit();
    }
    void DrawText(int fontTexture, string text, float size);
    GLuint LoadTexture(const char *image_path);
    
    void RenderTitle() {
        
        DrawText(fontSheetTexId, "Space Invaders", 0.1f );
        
    }
    
    
    
    
    
    
    bool done;
    float lastFrameTicks;
    SDL_Event event;
    int state;
    GLuint mainSpriteSheet;
    GLuint fontSheetTexId;
    int score;
    
};
class SheetSprite {
public:
    
    SheetSprite();
    SheetSprite(unsigned int textureID, float u, float v, float width, float height);
    void Draw(float scale);
    float scale;
    unsigned int textureID;
    float u;
    float v;
    float width;
    float height;
    
};*/


class Entity {
public:
    
    //constructor for entity
    Entity(float x_pos, float y_pos, float width, float height, float index, int spriteY, int spriteX, bool visible):x_pos(x_pos), y_pos(y_pos),width(width),height(height),index(index),spriteCountY(spriteY), spriteCountX(spriteX),visible(visible){};
    
    
    void DrawSpriteSheetSprite() ;
    
    
    void Kill() {
        visible = false;
    }
    
    void Move(float elapsed) {
      
        if ( x_pos >= 1.0 ) {
          direction_x = -direction_x;
        }
        if ( x_pos <= -1.0 ) {direction_x = -direction_x;}
        
        x_pos += direction_x * speed * elapsed;
        //y_pos += direction_y * speed * elapsed;
     
    }
    
    GLuint LoadTexture(const char *image_path) {
        SDL_Surface *surface = IMG_Load(image_path);
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                     GL_UNSIGNED_BYTE, surface->pixels);
        
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(surface);
        return textureID;
    }
    
    GLuint textureID = LoadTexture("53209.png");
    float x;
    float y;
    float rotation;
    
    //  int textureID;
    float width;
    float height;
    float speed = 0.5;
    float direction_x = 0.5;
    float direction_y = 0.0 ;
    float scale;
    bool visible;
    float spriteIndex;
    int spriteTexture;
    int index;
    int spriteCountX;
    int spriteCountY;
    float x_pos;
    float y_pos;
};




void DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x_pos, float y_pos) {
    
    glLoadIdentity();
    glTranslatef(x_pos, y_pos, 0.0);
    
    
    
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float texture_size = 1.0/16.0f;
    vector<float> vertexData;
    vector<float> texCoordData;
    vector<float> colorData;
    for(int i=0; i < text.size(); i++) {
        float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
        float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
        colorData.insert(colorData.end(), {r,g,b,a, r,g,b,a, r,g,b,a, r,g,b,a});
        vertexData.insert(vertexData.end(), {((size+spacing) * i) + (-0.5f * size), 0.5f * size, ((size+spacing) * i) +
            (-0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), 0.5f
            * size});
        
        
        texCoordData.insert(texCoordData.end(), {texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
            texture_size, texture_y + texture_size, texture_x + texture_size, texture_y});
        
        
    }
    
    
    
    
    glColorPointer(4, GL_FLOAT, 0, colorData.data());
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glDrawArrays(GL_QUADS, 0, text.size() * 4);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Entity::DrawSpriteSheetSprite() {
    
    
    
    
    
    float u = (float)(((int)index) % spriteCountX) / (float) spriteCountX;
    float v = (float)(((int)index) / spriteCountX) / (float) spriteCountY;
    float spriteWidth = 1.0/(float)spriteCountX;
    float spriteHeight = 1.0/(float)spriteCountY;
    GLfloat quadUVs[] = { u, v,
        u, v+spriteHeight,  u+spriteWidth, v+spriteHeight,
        u+spriteWidth, v
    };
    
    
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x_pos, y_pos, 0.0);
    
    GLfloat quad[] = {-width, height, -width, -height, width, -height, width, height};
    
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
    
    
}

void DrawSprite(GLint texture, float x, float y, float rotation, float w, float h) {
    
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    //image size quad[]
    
    //definiting the image size by the coordinate from the parameter
    GLfloat quad[] = {-w, h, -w, -h, w, -h, w, h};
    
    glVertexPointer(2, GL_FLOAT, 0, quad);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    
    // GLfloat quadUVs[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    //enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
    
    
}

GLuint LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                 GL_UNSIGNED_BYTE, surface->pixels);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    return textureID;
}

class Bullet{
public:
    
    Bullet(float x, float y, float angle, float w, float h , bool shoot=  false):
    x(x),y(y),angle(angle),w(w),h(h){};
    
    void Shoot(){
        
        for (int i =0; i < bullets.size(); i++ ){
            if( bullets[i]->shoot == true ) { bullets[i]->draw(); }
        }
        
        
    }
    
    
    void draw(){
        
        glLoadIdentity();
        glTranslatef(x, y, 0.0);
        glRotatef(angle, 0.0, 0.0, 1.0);
        
        
        //  GLfloat quad[] = {-x, y, -x, -y, x, -y, x, y};
        GLfloat quad[] = {-w, h, -w, -h, w, -h, w, h};
        glVertexPointer(2, GL_FLOAT, 0, quad);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_QUADS, 0, 4);
        
        //  GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
        //glTexCoordPointer(2, GL_QUADS, 0, quadUVs);
        
        
    }
    
    float x;
    float y;
    float angle;
    float w;
    float h;
    bool shoot;
    vector<Bullet*> bullets;
    //float bullet_y = gun_y;
    int unused_bullets = MAX_BULLETS;
    
    
};





 
 bool checkCollision(Entity p1, Bullet ball){
     //if ball x y is between the entity x+-w/2 and if ball y + h/2 > entity x +h/2 then its colliding
 
 
   //  if ((ball.y - ball.h * 0.5) > (p1.y + p1.height * 0.5))  return true;
     
     //if the left side of ball is bigger than the entity left side, then its not colliding
     if ( ball.x - ball.w*0.5  > p1.x_pos+ p1.width*0.5 ) return false;
     //if the right side of ball is bigger than the entity right side, then its not colliding
     if ( ball.x + ball.w*0.5 < p1.x_pos- p1.width*0.5 ) return false;
     //if the ball x+width/2 position is less than the entity x-w/2 then its not colliding
     if ( ball.y + ball.h*0.5 < p1.x_pos - p1.height*0.5  ) return false;
     
     if ( ball.y - ball.h*0.5 > p1.x_pos + p1.height*0.5  ) return false;
     
 
     return true;
 }



 
 void displayScore(int score, GLuint font){
    
     string scoreText ="Current Score: ";
     string scoreString = to_string(score);
     scoreText = scoreText+" " + scoreString;
     DrawText(font, scoreText, 0.05f, 0.02f, 1.0f,1.0f, 1.0f, 1.0f, -0.6, 0.9);
   

     
 }
 


void drawBackground(){
    
     GLuint bg = LoadTexture("clouds-vector-backgrounds.jpg");
     DrawSprite(bg, 0.0, 0.0, 0.00, 1.00, 1.00);
    
}

void titleScreen(){
    
    drawBackground();
    GLuint font = LoadTexture("pixel_font.png");
    DrawText(font, "Space Invaders", 0.05f, 0.02f, 0.0f, 1.0f, 1.0f, 1.0f, -0.4, 0.8);
    
    
    
    // DrawSprite(spaceInvadersSprite, 0.0, 0.0, 0.00, 1.00, 1.00);
}


int main(int argc, char *argv[]){
    
    
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Space Invader", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    bool done = false;
    
    SDL_Event event;
    
    float lastFrameTicks = 0.0;
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
     GLuint font = LoadTexture("pixel_font.png");
     GLuint gun = LoadTexture("gun.png");
   
    vector<Entity> entities;
    float gun_x=0.0;
    float gun_y=-0.8;
    float positionX = -0.8;
    
    float positionY = 0.9;
    int index = 0;
    vector<Entity> theGuys;
    vector<Bullet> bullets;
    
    int score=0;
    int count=0;
    

  //------------------entity----------------------------------
    
    for (int i =0; i < MAX_GUYS; i++ ){
        
        if(index == 6 ) index = 0;
        if (positionX > 0.8) positionX =-0.8;
       // if ( i == 9 ) positionY -= 0.2;
         if ( i % 9 == 0 ) positionY -= 0.2;
        Entity* e1 = new Entity(positionX, positionY, 0.05, 0.05, index, 16,16, true);
        theGuys.push_back(*e1);
        positionX+=0.2;
        index++;
        
    }
    
  //----------------------------------------------------
    
    
    for ( int i = 0; i < MAX_BULLETS; i++){
        Bullet* bullet = new Bullet(gun_x, gun_y, 0.0, 0.005,0.02);
        bullets.push_back(*bullet);
        
    }
    
    
  //  GLuint bg = LoadTexture("ScreenshotStarfield.png");
    GLuint bg = LoadTexture("artwork-galaxies-space-1024x768.jpg");
  
    
    
    while (!done) {
        
        
        
         glClear(GL_COLOR_BUFFER_BIT);
        
        
        
        
        //TIMER----------------------------------------------
        float ticks = (float)SDL_GetTicks()/1000.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;
       
       //----------------------------------------------------
      
       
        
    
    //------------------keyboard----------------------------------
        while (SDL_PollEvent(&event)) {
          
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) { done = true; }
            
            if (event.type == SDL_KEYDOWN ){
            
            if(event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                gun_x -= 0.04;
                bullets[count].x = gun_x;
                
            }
            if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                gun_x += 0.04;
                bullets[count].x = gun_x;
 
            }
        if(event.key.keysym.scancode == SDL_SCANCODE_UP){
        
            bullets[count].y = gun_y;
            bullets[count].x = gun_x;

            count++;
            
        }
            }
            
        }
        
    //----------------------------------------------------
        
        
        
        // titleScreen();
     
        
       
        DrawSprite(bg, 0.0, 0.0, 0.00, 1.00, 1.00);
        
        displayScore(score, font);
       
        DrawSprite(gun, gun_x, gun_y, 0.00, 0.05, 0.05);
        
        
        
        for (int i =0; i < bullets.size(); i++ ){
            
            bullets[i].y += elapsed;
            bullets[i].draw();
            
        }
        
        
        

    for(int j =0; j< bullets.size(); j++ ){
            for (int i =0; i < theGuys.size(); i++ ){
        
                if(checkCollision( theGuys[i], bullets[j] )){
                    theGuys[i].Kill();
                    score+=10;
               }
            }
            
            }

    
       
      
    for (int i =0; i < theGuys.size(); i++ ){
      if ( theGuys[i].visible == true ) {
               if(i >= 0 && i < 9 ) theGuys[i].Move(elapsed*1.1);
              if(i >= 9 && i < 18 ) theGuys[i].Move(elapsed*0.8);
             if(i >= 18 && i < 27 ) theGuys[i].Move(elapsed*1.7);
             if(i >= 27 && i < 36 ) theGuys[i].Move(elapsed*0.5);
             if(i >= 36 && i < 45 ) theGuys[i].Move(elapsed*1.3);
                       theGuys[i].DrawSpriteSheetSprite();
        }
        }
            
        
        
        
     
      
        SDL_GL_SwapWindow(displayWindow);
        
       
        
        
    }
    
    
   
    SDL_Quit();
    return 0;
    
    
}