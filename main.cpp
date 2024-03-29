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
            vector<cv::Rect> faces; // pixles for frontal face, vector for multiple faces
            face_model.detectMultiScale(frame,
                                        faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE,
                                        cv::Size(30, 30));

            for (int i = 0; i < faces.size(); i++)
            {
                cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2); // Get the center of faces[i]
                ellipse(fame, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv : Scalar(255, 0, 255), 4, 8, 0);
            }

            cv::imshow("video", frmae);
        }

        cv::imshow("video", frame);

        char c = (char)cv::waitKey(10);

        if (c == 27) // ESC on Keyboard: ascii = 27
            break;
    }

    return 0;
}

int rec_camera()
{
    int camera_id = 0;
    cv::VideoCapture cap;
    cap.open(camera_id);
    cv::Mat frame;

    cv::VideoWriter output_video;

    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    output_video.open("%d:/rec.avi", CV_FOURCC("M", "J", "P", "G", 30.0, cv::Size(width, height)));

    for (;;)
    {
        cap >> frame;
        if (frame.empty())
            break;

        cv::imshow("video", frame); // Output one bit of video each time

        output_video.write(frame);

        char c = (char)cv::waitKey(10) // Waiting for Key from keyboard every 10 ms

            if (c == 27) break;
    }

    return 0;
}