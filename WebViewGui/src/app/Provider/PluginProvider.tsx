import { useEffect } from 'react';

import * as Juce from 'juce-framework-frontend';
import { usePluginStore } from '@/store/PluginStore';

export default function App() {
  const {
    setPluginInfo,
    setNumChannels
  } = usePluginStore();

  useEffect(() => {
    fetch(Juce.getBackendResourceAddress('plugin.json'))
      .then((response) => response.json())
      .then((data) => {
        console.log(data);
        if (data) {
          setPluginInfo({
            pluginVersion: data.pluginVersion,
            pluginName: data.pluginName,
            companyName: data.companyName
          });
          setNumChannels(data.outputNumChannels);
        }

        return null;
      }).catch(console.error);
  }, [setNumChannels, setPluginInfo]);

  return null;
}
