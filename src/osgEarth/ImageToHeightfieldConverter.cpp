#include <osgEarth/ImageToHeightFieldConverter>

#include <osg/Notify>

using namespace osgEarth;

osg::HeightField* ImageToHeightFieldConverter::convert(osg::Image* image, float scaleFactor)
{
    //osg::notify(osg::NOTICE) << "Scale factor " << scaleFactor << std::endl;
	osg::HeightField *hf = new osg::HeightField;
	if (!image)
	{
		osg::notify(osg::WARN) << "Image null, returning empty heightfield" << std::endl;
		hf->allocate( 8, 8 );
        for(unsigned int i=0; i<hf->getHeightList().size(); i++ )
            hf->getHeightList()[i] = 0;//(double)((::rand() % 10000) - 5000);
	}
	else
	{
		//osg::notify(osg::NOTICE) << "Read heightfield image" << std::endl;
		hf->allocate(image->s(), image->t());
				
		for( unsigned int row=0; row < image->t(); row++ ) {
            //osg::notify(osg::NOTICE) << "ROW " << row << ":\t";
            for( unsigned int col=0; col < image->s(); col++ ) {
                unsigned char* ptr = image->data( col, row );
                if ( image->getPixelSizeInBits() == 16 ) {
                    short val = (short)*(short*)ptr;
                    hf->setHeight( col, row, ((float)val) * scaleFactor );
                    //osg::notify(osg::NOTICE) << val << "\t";
                }
                else if ( image->getPixelSizeInBits() == 32 ) {
                    float val = (float)*(float*)ptr;
                    hf->setHeight( col, row, val * scaleFactor );
					//osg::notify(osg::NOTICE) << val << "\t";
                }
            }
            //osg::notify(osg::NOTICE) << std::endl;
        }
	}
	return hf;
}