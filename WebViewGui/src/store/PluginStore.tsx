import { create } from 'zustand';

interface PluginInfo {
  pluginVersion: string;
  pluginName: string;
  companyName: string;
}

const defaultPluginInfo: PluginInfo = {
  pluginVersion: '',
  pluginName: '',
  companyName: '',
};

interface PluginState {
  pluginInfo: PluginInfo;
  setPluginInfo: ({ pluginVersion }: PluginInfo) => void;

  numChannels: number;
  setNumChannels: (value: number) => void;
}

export const usePluginStore = create<PluginState>((set) => ({
  pluginInfo: defaultPluginInfo,
  setPluginInfo: (value: PluginInfo) => set({ pluginInfo: value }),

  numChannels: 0,
  setNumChannels: (value: number) => set({ numChannels: value }),
}));
