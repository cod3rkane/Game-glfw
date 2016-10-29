//
//  Created by Cod3r Kane on 10/22/2016
//

#ifndef GAME_RAWMODEL_H
#define GAME_RAWMODEL_H

#include <GL/glew.h>

class RawModel {
private:
    GLuint VaoID;
    GLuint VertexCount;
public:

    /**
     * Normal constructor class
     * @param int VaoID
     * @param int VertexCount
     */
    RawModel(GLuint VaoID, GLuint VertexCount);

    /**
     * Empty constructor class
     */
    RawModel() {};

    /**
     * Get VaoID
     * @return int
     */
    GLuint getVaoID() const;

    /**
     * set VaoID
     * @param int VaoID
     */
    void setVaoID(GLuint VaoID);

    /**
     * get VertexCount
     * @return int
     */
    GLuint getVertexCount() const;

    /**
     * set VertexCount
     * @param int VertexCount
     */
    void setVertexCount(GLuint VertexCount);
};

#endif // GAME_OBJLOADER_H