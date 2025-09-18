'use client';

import { useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

const pressSpace = Juce.getNativeFunction('pressSpace');

export default function GlobalSpaceListener() {
  useEffect(() => {
    const handleKeyDown = (event: KeyboardEvent) => {
      if (event.code === 'Space') {
        pressSpace();
        event.preventDefault();
      }
    };

    window.addEventListener('keydown', handleKeyDown);

    return () => {
      window.removeEventListener('keydown', handleKeyDown);
    };
  }, []);

  return null;
}
