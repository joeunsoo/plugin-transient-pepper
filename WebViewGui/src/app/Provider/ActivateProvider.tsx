import { useActivateStore } from '@/store/ActivateStore';
import Activate from '@/ui/Activate';

import * as Juce from 'juce-framework-frontend';
import { useEffect } from 'react';

const getActivate = Juce.getNativeFunction('getActivate');

export default function App() {
  const { setOpen, setActivate } = useActivateStore();

  useEffect(() => {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    getActivate().then((result: any) => {
      if (result.length < 1) {
        setActivate(false);
        setOpen(true);
      } else {
        setActivate(true);
      }

      return null;
    }).catch(null);
  }, [setActivate, setOpen]);

  return (
    <Activate />
  );
}
