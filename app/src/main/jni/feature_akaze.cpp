#include <jni.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif


cv::Mat smallImg;

JNIEXPORT void JNICALL
Java_ph_edu_dlsu_akaze_MainActivity_findAKAZEFeatures(JNIEnv *env, jobject instance,
                                                      jlong mGray, jlong mRgba) {

    cv::Mat& mGr  = *(cv::Mat*)mGray;
    cv::Mat& mRgb = *(cv::Mat*)mRgba;

    jint scale = 2;

    if (smallImg.empty())
        smallImg.create( mGr.rows/scale, mGr.cols/scale, CV_8UC1);

    cv::resize( mGr, smallImg, smallImg.size(), cv::INTER_LINEAR );

    std::vector<cv::KeyPoint> v;

    cv::Ptr<cv::Feature2D> detector = cv::AKAZE::create();

    //cv::Ptr<cv::Feature2D> detector = cv::AKAZE::create(cv::AKAZE::DESCRIPTOR_MLDB, 0, 3, 0.0001f,4,4, cv::KAZE::DIFF_PM_G2);

    /*
     Ptr<AKAZE> create(
     (int descriptor_type=AKAZE::DESCRIPTOR_MLDB,
    int descriptor_size = 0, int descriptor_channels = 3,
    float threshold = 0.001f, int nOctaves = 4,
    int nOctaveLayers = 4, int diffusivity = KAZE::DIFF_PM_G2)
    */

    detector->detect(smallImg, v);

    for( unsigned int i = 0; i < v.size(); i++ )
    {
        const cv::KeyPoint& kp = v[i];
        cv::circle(mRgb, cv::Point(kp.pt.x*scale, kp.pt.y*scale), 10, cv::Scalar(0,255,0,255));
    }

}

#ifdef __cplusplus
}
#endif