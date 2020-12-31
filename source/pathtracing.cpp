#include "pathtracing.h"
#include "sample.h"

PathTracing::PathTracing()
{
    this->camera = new Camera();
    this->frame = new Frame();
}

PathTracing::~PathTracing()
{
    delete this->camera;
    delete this->frame;
}

vector3D PathTracing::illuminate(Ray &r, Intersection &itsn)
{
    vector3D illumination(0, 0, 0);
    const double PI = acos(-1);
    for(unsigned int i = 0; i < this->frame->lights.size(); i++){
        vector3D ilm_p(0, 0, 0);
        for(int j = 0; j < this->numSmpinLight; j++){
            vector3D position = r.origin + r.direction * itsn.distance;
            double length, cosTheta_l, lightArea;
            Ray sampleRay = this->frame->lights[i]->genLightRay(position, length, cosTheta_l, lightArea);
            if(lightArea < 1e-6)
                continue;
            double cosTheta = scalarProduct(sampleRay.direction, itsn.normal);
            if(cosTheta < 0)
                continue;
            if(!this->frame->isShield(sampleRay, length)){
                if(itsn.matl->Kd.module() > 0){
                    vector3D brdf = itsn.matl->Kd / PI;
                    ilm_p = ilm_p + this->frame->lights[i]->emssion * lightArea * (cosTheta_l * cosTheta) / (length * length) * brdf;
                }
                if(itsn.matl->Ks.module() > 0){
                    vector3D H = (sampleRay.direction - r.direction).normalize();
                    vector3D brdf = pow(scalarProduct(H, itsn.normal), itsn.matl->Ns) * itsn.matl->Ks * (itsn.matl->Ns + 8) / (8 * PI);
                    ilm_p = ilm_p + this->frame->lights[i]->emssion * lightArea * (cosTheta_l * cosTheta) / (length * length) * brdf;
                }
            }
        }
        if(this->numSmpinLight > 0)
            illumination = illumination + ilm_p / double(numSmpinLight);
    }
    return illumination;
}

vector3D PathTracing::rayTracing(Ray &r, int depth)
{
    if(depth > maxDepth)
        return vector3D(0, 0, 0);
    Intersection itsn;
    const double PI = acos(-1);
    if(this->frame->intersect(r, itsn)){
        if((this->ambientLight * itsn.matl->Ka).module() > sqrt(3.0)){
            if(depth != 0){
                return vector3D(0, 0, 0);
            }
            else{
              return (this->ambientLight * itsn.matl->Ka);
            }
        }
        vector3D indirectLight;
        vector3D directLight = this->illuminate(r, itsn);
        vector3D position = r.origin + r.direction * itsn.distance * 0.999999;
        if(itsn.matl->Ni > 1.4){
            // Ni > 1.4, Refraction
            double cosTheta_inci = scalarProduct(r.direction, itsn.normal); // angle of incidence
            vector3D refractionDirection;
            if(cosTheta_inci < 0){
                // cos(Theta_r_n) < 0, ray points to inside.
                cosTheta_inci = abs(cosTheta_inci);
                double sinTheta_inci = sqrt(1.0 - cosTheta_inci * cosTheta_inci);
                double sinTheta_exit = sinTheta_inci / itsn.matl->Ni;
                double cosTheta_exit = sqrt(1.0 - sinTheta_exit * sinTheta_exit);
                refractionDirection = r.direction - (cosTheta_exit * itsn.matl->Ni - cosTheta_inci) * (itsn.normal.normalize());
            }
            else{
                // cos(Theta_r_n) > 0, ray points to outside.
                // especially, cause Ni > 1, while the ray goes out of the material, it may cause total interial reflection
                // if total interial reflection, theta_exit > PI / 2, cos(theta_exit) < 0
                double sinTheta_inci = sqrt(1.0 - cosTheta_inci * cosTheta_inci);
                double sinTheta_exit = sinTheta_inci * itsn.matl->Ni;
                double cosTheta_exit_square = 1.0 - sinTheta_exit * sinTheta_exit;
                if(cosTheta_exit_square > 0){
                    double cosTheta_exit = sqrt(1.0 - sinTheta_exit * sinTheta_exit);
                    refractionDirection = r.direction - (cosTheta_inci - cosTheta_exit / itsn.matl->Ni) * (itsn.normal.normalize());
                }

            }
            if(refractionDirection.module() > 1e-6){
                Ray refractionRay(position, refractionDirection.normalize());
                indirectLight = indirectLight + this->rayTracing(refractionRay, depth + 1);
            }
        }
        else{
            // reflection: specular reflection and diffuse reflection
            if(scalarProduct(itsn.normal, r.direction) > 0)
                return vector3D(0, 0, 0);
            // ratio of specular reflection and diffuse reflection
            // sf: specular reflection
            // df: diffuse reflection
            double sfRatio = itsn.matl->Ks[0] + itsn.matl->Ks[1] + itsn.matl->Ks[2];
            double dfRatio = itsn.matl->Kd[0] + itsn.matl->Kd[1] + itsn.matl->Kd[2];
            double sumRatio = sfRatio + dfRatio;
            sfRatio = sfRatio / sumRatio;
            double randomRatio = double(rand()) / double(RAND_MAX);
            Ray sampleRay;
            vector3D ogIndirectLight;
            double pdf; // probility distribution function
            if(randomRatio < sfRatio){
                // specular reflection
                sampleRay = Sample::specularReflectionSample(position, itsn.normal, r.direction, itsn.matl->Ns, pdf);
                ogIndirectLight = this->rayTracing(sampleRay, depth + 1);
                // H stands for half angle vector
                vector3D H = (sampleRay.direction - r.direction).normalize();
                vector3D brdf = (itsn.matl->Ns + 8) / (8 * PI) * pow(scalarProduct(H, itsn.normal), itsn.matl->Ns) * itsn.matl->Ks;
                indirectLight = indirectLight + ogIndirectLight * brdf / pdf * scalarProduct(itsn.normal, sampleRay.direction);
            }
            else{
                // diffuse reflection
                sampleRay = Sample::diffuseReflectionSample(position, itsn.normal, pdf);
                ogIndirectLight = this->rayTracing(sampleRay, depth + 1);
                indirectLight = indirectLight + itsn.matl->Kd * ogIndirectLight;
            }
        }
        return directLight + indirectLight + this->ambientLight * itsn.matl->Ka;
    }
    return vector3D(0, 0, 0);
}

void PathTracing::render()
{
    double gamma = 2.2;
    vector<vector<vector3D>> imageRGB(static_cast<unsigned int>(this->camera->width), vector<vector3D>(static_cast<unsigned int>(this->camera->height), vector3D(0, 0, 0)));
    for(int i = 0; i < this->camera->width; i++){
        for(int j = 0; j < this->camera->height; j++){
            vector3D rgb;
            for(int k = 0; k < numRayinPixel; k++){
                Ray pixelSampleRay = this->camera->genRay(i, j);
                Intersection itsn;
                rgb = rgb + this->rayTracing(pixelSampleRay, 0);
            }
            rgb = rgb / double(numRayinPixel);
            for(int k = 0; k < 3; k++){
                rgb[k] = pow(double(rgb[k]), 1.0 / gamma);
                rgb[k] = (rgb[k] > 0.999) ? 0.999 : rgb[k];
                rgb[k] = (rgb[k] < 0) ? 0 : rgb[k];
                rgb[k] = 255 * rgb[k];
            }
            imageRGB[static_cast<unsigned int>(i)][static_cast<unsigned int>(j)] = rgb;
        }
        cout << double(i + 1) / double(camera->width) * 100 << "%" << endl;
    }
    this->image = imageRGB;
}
