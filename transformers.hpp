#ifndef TRANSFORMERS_HPP
#define TRANSFORMERS_HPP

void init_structures(void);
void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[]);
void drawHemisphere(float radius, int longSlices, int latSlices,int p,int q,int in);
void drawCylinder(float br,float tr, float h,int lon,int lat,int p,int q);

extern GLfloat mat_specularWHITE[];
extern GLfloat mat_ambientWHITE[];
extern GLfloat mat_diffuseWHITE[];
extern GLfloat mat_shininessWHITE[];

#endif // TRANSFORMERS_HPP
