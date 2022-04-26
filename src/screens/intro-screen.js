import React, { useEffect, useState } from 'react';
import {
  View,
  Platform,
  TouchableOpacity,
  StyleSheet,
  Text,
  TextInput
} from 'react-native';
import {
  check,
  request,
  openSettings,
  PERMISSIONS,
  RESULTS,
} from 'react-native-permissions';
import { ZOOM_APP_KEY, ZOOM_APP_SECRET } from '../../config';
import size from '../theme/fonts';
import metrics from '../theme/metrics';


const platformPermissions = {
  ios: PERMISSIONS.IOS.MICROPHONE,
  android: PERMISSIONS.ANDROID.RECORD_AUDIO,
};

export function IntroScreen({ navigation }) {

  const [zoomAppKey, setZoomAppKey] = useState(ZOOM_APP_KEY)
  const [zoomAppSecret, setZoomAppSecret] = useState(ZOOM_APP_SECRET)

  useEffect(() => {
    const permissions = platformPermissions[Platform.OS];

    check(permissions).then(
      (status) => {
        if (status === RESULTS.BLOCKED) {
          openSettings()
        } else if (status !== RESULTS.GRANTED) {
          request(permissions)
        }
      });

    if (ZOOM_APP_KEY && ZOOM_APP_SECRET) {
      navigation.navigate('Join', {
        zoomAppKey,
        zoomAppSecret,
      })
    }
  }, []);

  return (
    <View style={styles.container} >
      <Text style={styles.text}>Zoom App Key</Text>
      <TextInput
        style={styles.input}
        value={zoomAppKey}
        onChangeText={setZoomAppKey}
        placeholderTextColor={'grey'}
      />
      <Text style={styles.text}>Zoom App Secret</Text>
      <TextInput
        style={styles.input}
        value={zoomAppSecret}
        onChangeText={setZoomAppSecret}
        placeholderTextColor={'grey'}
      />
      <TouchableOpacity
        style={styles.button}
        onPress={() =>
          zoomAppKey && zoomAppSecret &&
          navigation.navigate('Join', {
            zoomAppKey,
            zoomAppSecret,
          })
        }
      >
        <Text style={styles.buttonText}>Next</Text>
      </TouchableOpacity>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "black",
    paddingTop: metrics.height / 5
  },
  text: {
    color: "grey",
    alignSelf: 'center',
    fontSize: size(18),
    fontWeight: "bold",
    marginBottom: metrics.height / 80,
  },
  input: {
    backgroundColor: "grey",
    alignSelf: 'center',
    fontSize: size(18),
    width: metrics.width / 1.3,
    borderRadius: metrics.height / 72,
    marginBottom: metrics.height / 36,
    paddingLeft: metrics.width / 36,
    paddingVertical: metrics.height / 110
  },
  button: {
    backgroundColor: "orange",
    alignItems: 'center',
    marginTop: metrics.height / 72,
    width: metrics.width / 3,
    alignSelf: 'center',
    borderRadius: metrics.height / 100,
  },
  buttonText: {
    color: "white",
    marginVertical: metrics.height / 100,
    fontSize: size(18)
  },
})