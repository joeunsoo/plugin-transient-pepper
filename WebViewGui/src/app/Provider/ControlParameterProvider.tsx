import * as Juce from 'juce-framework-frontend';

import { controlParameterIndexAnnotation } from '@/define';

export default function Provider() {
  const controlParameterIndexUpdater = new Juce.ControlParameterIndexUpdater(
    controlParameterIndexAnnotation
  );

  document.addEventListener('mousemove', (event) => {
    controlParameterIndexUpdater.handleMouseMove(event);
  });

  return null;
}
