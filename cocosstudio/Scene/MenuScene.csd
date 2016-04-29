<GameFile>
  <PropertyGroup Name="MenuScene" Type="Scene" ID="5f965142-f60f-4aff-87d5-250f602556e7" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="60" Speed="1.0000">
        <Timeline ActionTag="-2143044260" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="1.2000" Y="1.2000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <ObjectData Name="Scene" Tag="6" ctype="GameNodeObjectData">
        <Size X="1136.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="bg_1" ActionTag="1992028897" Tag="7" IconVisible="False" ctype="SpriteObjectData">
            <Size X="1136.0000" Y="640.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="Images/Menu/bg.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="startbt" ActionTag="-2143044260" Tag="9" IconVisible="False" LeftMargin="472.5000" RightMargin="442.5000" TopMargin="567.5000" BottomMargin="51.5000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="6" BottomEage="6" Scale9OriginX="15" Scale9OriginY="6" Scale9Width="191" Scale9Height="9" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="221.0000" Y="21.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="583.0000" Y="62.0000" />
            <Scale ScaleX="1.0067" ScaleY="1.0067" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5132" Y="0.0969" />
            <PreSize X="0.1945" Y="0.0328" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="Images/Menu/startbt.png" Plist="" />
            <NormalFileData Type="Normal" Path="Images/Menu/startbt.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>