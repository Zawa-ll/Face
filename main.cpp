#include <opencv2/opencv.hpp>

using namespace std;
int main()
{
}

// Method for showing an image
int show_img()
{
    cv::Mat img = cv::imread("tools/cat.png", -1);

    if (img.empty())
        return -1;

    cv::namedWindow("cat", cv::WINDOW_AUTOSIZE);
    cv::imshow("cat", img);
    cv::waitKey(0); // remain open when set to 0
    cv::destroyWindow("cat");

    return 0;
}

// Method for showing a video
int show_video()
{
    cv::VideoCapture cap;
    cv::namedWindow("video", cv::WINDOW_AUTOSIZE);
    cap.open("tools/test.avi");
    cv::Mat frame; // fram for receiving every byte of image

    for (;;)
    {
        cap >> frame; // input bits from video till no bit left
        if (frame.empty())
            break;

        cv::imshow("video", frame);

        char c = (char)cv::waitKey(200);

        if (c == 27) // ESC on Keyboard: ascii = 27
            break;
    }
    return 0;
}

int camera()
{
    int camera_id = 0;
    cv::VideoCapture cap;
    cap.open(canera_id);
    cv::Mat frame;

    bool is_face = false;

    cv::CascadeClassifier face_model;
    if (is_face)
    {
        char *face_model_path = "tools/haarcascade_frontalface_alt.xml"; // Face Model provide by OpenCV
        if (!face_model.load(face_model_path))
        {
            return -1; // fail to read frontalface model
        }
    }

    for (;;)
    {
        cap >> frame;
        if (frame.empty()) // Camera captures nothing: first bit capture is empty
            break;

        if (is_face)
        {
            // TODO:
            // vector<cv::Rect> faces; // pixles for frontal face, vector for multiple faces
            // face_model.detectMultiScale(frame,
            //                             faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE,
            //                             cv::Size(30, 30));

            // for (int i = 0; i < faces.size(); i ++ ) {

            // }
        }

        cv::imshow("video", frame);

        char c = (char)cv::waitKey(10);

        if (c == 27) // ESC on Keyboard: ascii = 27
            break;
    }

    return 0;
}