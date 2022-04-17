import cv2 
from keras.models import load_model 
import numpy as np 

np.set_printoptions(suppress=True)

model = load_model('models/keras_model.h5')
data = np.ndarray(shape=(1, 224, 224, 3), dtype=np.float32)

cam = cv2.VideoCapture('http://192.168.216.128:4747/video')

while True:
    _, frame= cam.read()

    img = cv2.resize(frame ,(224, 224))
    image_array = np.asarray(img)
    normalized_image_array = (image_array.astype(np.float32) / 127.0) - 1
    data[0] = normalized_image_array

    prediction = model.predict(data)

    if prediction[0, 0] > .7 and prediction[0, 1] < .3 and prediction[0, 2] < .3:
        cv2.putText(frame, f'Forward : {prediction[0, 0]}', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (50, 255, 0), 2)
    elif prediction[0, 1] > .7 and prediction[0, 0] < .3 and prediction[0, 2] < .3:
        cv2.putText(frame, f'Back : {prediction[0, 0]}', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (50, 255, 0), 2)
    elif prediction[0, 2] > .7 and prediction[0, 0] < .3 and prediction[0, 1] < .3:
        cv2.putText(frame, f'Left : {prediction[0, 0]}', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (50, 255, 0), 2)

    cv2.imshow('img',frame)
    if cv2.waitKey(1) & 0xFF == ord('q') :
        break

cam.release()
cv2.destroyAllWindows()