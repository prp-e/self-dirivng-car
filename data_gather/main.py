import cv2 
from uuid import uuid4

cam = cv2.VideoCapture("http://192.168.216.128:4747/video")

while cam.isOpened():
    ret, frame = cam.read()
        
    
    if cv2.waitKey(1) & 0xFF == ord('f'):
        cv2.imwrite('forward-' + str(uuid4()) + ".jpg", frame)
        
    if cv2.waitKey(1) & 0xFF == ord('b'):
        cv2.imwrite('back-' + str(uuid4()) + ".jpg", frame)

    if cv2.waitKey(1) & 0xFF == ord('l'):
        cv2.imwrite('left-' + str(uuid4()) + ".jpg", frame)
        
    if cv2.waitKey(1) & 0xFF == ord('r'):
        cv2.imwrite('right-' + str(uuid4()) + ".jpg", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
    cv2.imshow("frame", frame)

cv2.destroyAllWindows()
cam.release()