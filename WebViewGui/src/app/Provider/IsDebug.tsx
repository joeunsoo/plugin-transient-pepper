import Activate from '@/ui/Activate';

import * as Juce from 'juce-framework-frontend';
import { useEffect } from 'react';

const isDebug = Juce.getNativeFunction('isDebug');

export default function App() {
  useEffect(() => {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    isDebug().then((result: boolean) => {
      if (!result) {
        document.addEventListener('contextmenu', () => false);
        document.addEventListener('selectstart', () => false);
        document.addEventListener('dragstart', () => false);
      }

      return null;
    }).catch(console.error);
  }, []);

  return (
    <Activate />
  );
}
