import * as React from 'react';
import { ZoomVideoSdkProvider } from '@zoom/react-native-videosdk';
import { NavigationContainer } from '@react-navigation/native';
import MainNavigation from './navigation';
import { StatusBar } from 'react-native';

export default function App() {
  return (
    <NavigationContainer>
      <StatusBar hidden />
      <ZoomVideoSdkProvider
        config={{
          appGroupId: '', // add apple team id 
          domain: 'zoom.us',
          enableLog: true,
        }}
      >
        <MainNavigation />
      </ZoomVideoSdkProvider>
    </NavigationContainer>
  );
}
