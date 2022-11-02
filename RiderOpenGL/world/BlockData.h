/**
 * \brief Stocke les données d'un bloc qui pour l'instant est affiché pour montrer le rendu d'objet
 */
class BlockData
{

public:
	/**
	 * \brief Chemin jusque la texture du bloc
	 */
	inline static const char* filePath = "res//textures//grass.png";

	/**
	 * \brief sommets primitifs du bloc
	 */
	inline static GLfloat vertices[] = {
    	-0.5f, 0.5f, 0.5f,
    	-0.5f, -0.5f, 0.5f,
    	 0.5f, -0.5f, 0.5f,
    	 0.5f, 0.5f, 0.5f,
    	-0.5f, 0.5f, -0.5f,
    	 0.5f, 0.5f, -0.5f,
    	-0.5f, -0.5f, -0.5f,
    	 0.5f, -0.5f, -0.5f,
    	-0.5f, 0.5f, -0.5f,
    	 0.5f, 0.5f, -0.5f,
    	-0.5f, 0.5f, 0.5f,
    	 0.5f, 0.5f, 0.5f,
    	 0.5f, 0.5f, 0.5f,
    	 0.5f, -0.5f, 0.5f,
    	-0.5f, 0.5f, 0.5f,
    	-0.5f, -0.5f, 0.5f,
    	-0.5f, -0.5f, -0.5f,
    	0.5f, -0.5f, -0.5f,
    	-0.5f, -0.5f, 0.5f,
    	0.5f, -0.5f, 0.5f,};

	/**
	 * \brief Coordoonnées de texture du bloc (en gros dans le .png ou est la texture, définit la région à utiliser pour le bloc)
	 */
	inline static GLfloat texCoords[] = {
    		0.0f, 0.0f,
            0.0f, 0.5f,
            0.5f, 0.5f,
            0.5f, 0.0f,
            0.0f, 0.0f,
            0.5f, 0.0f,
            0.0f, 0.5f,
            0.5f, 0.5f,
            0.0f, 0.5f,
            0.5f, 0.5f,
            0.0f, 1.0f,
            0.5f, 1.0f,
            0.0f, 0.0f,
            0.0f, 0.5f,
            0.5f, 0.0f,
            0.5f, 0.5f,
            0.5f, 0.0f,
            1.0f, 0.0f,
            0.5f, 0.5f,
            1.0f, 0.5f,
    };

	/**
	 * \brief permet la répétition de sommets (ex -> indices[0] = vertices[0], vertices[1] et vertices[2]; puisque on a des coordonnées 3d)
	 */
	inline static GLuint indices[] = {
        0, 1, 3, 3, 1, 2,
            8, 10, 11, 9, 8, 11,
            12, 13, 7, 5, 12, 7,
            14, 15, 6, 4, 14, 6,
            16, 18, 19, 17, 16, 19,
            4, 6, 7, 5, 4, 7,
    };


};