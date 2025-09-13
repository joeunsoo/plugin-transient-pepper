import { useActivateStore } from '@/store/ActivateStore';
import Activate from '@/ui/Activate';
import dayjs from 'dayjs';

import * as Juce from 'juce-framework-frontend';
import { useEffect } from 'react';

const getActivate = Juce.getNativeFunction('getActivate');

export default function App() {
  const { setOpen, setActivate, setTrial } = useActivateStore();

  useEffect(() => {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    getActivate().then((result: any) => {
      const activate = result.activate.length > 0;
      const trial = result.trial;
      if (activate) {
        setActivate(true);
      }
      if (trial > 0) {
        setTrial(trial);
      }

      const now = dayjs();
      const end = dayjs(trial).add(30, 'day');
      const trialEnded = now.isAfter(end); // true = 트라이얼 만료

      if (!activate && (!trial || trialEnded)) {
        setOpen(true);
      }

      return null;
    }).catch(null);
  }, [setActivate, setOpen, setTrial]);

  return (
    <Activate />
  );
}
