"""
@author: wangye(Wayne)
@license: Apache Licence
@file: opencv_FAST.py
@time: 20230207
@contact: wang121ye@hotmail.com
@site:  wangyendt@github.com
@software: PyCharm

# code is far away from bugs.
"""

import cv2
import time

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
pre_fps = 10
last_timestamp = time.time_ns() / 1e9
fps_win = 10
fast = cv2.FastFeatureDetector_create()
fast.setNonmaxSuppression(0)
while cap.isOpened():
    cur_timestamp = time.time_ns() / 1e9
    cur_fps = 1 / (cur_timestamp - last_timestamp)
    last_timestamp = cur_timestamp
    fps_n = pre_fps * fps_win
    fps_n -= (pre_fps - cur_fps)
    fps = fps_n / fps_win
    pre_fps = fps
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)
    kp = fast.detect(frame, None)
    frame = cv2.drawKeypoints(frame, kp, None, color=(0, 255, 0))
    print("Threshold: {}".format(fast.getThreshold()))
    print("nonmaxSuppression:{}".format(fast.getNonmaxSuppression()))
    print("neighborhood: {}".format(fast.getType()))
    print("Total Keypoints with nonmaxSuppression: {}".format(len(kp)))
    cv2.putText(frame, f'fps={fps:.3f}', (0, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 4)
    cv2.imshow("capture", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
