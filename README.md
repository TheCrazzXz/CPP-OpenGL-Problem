# CPP-OpenGL-Problem
There's no texture on the cube

Fixed by editing something in the src/object/Mesh.cpp

from in Mesh::setup :
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
to :
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
