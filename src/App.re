open ReasonUIKit;

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(State.reducer, State.initialState);

  React.useEffect0(() => {
    let timer = Js.Global.setInterval(() => dispatch(Tick), 1000);
    Some(() => Js.Global.clearInterval(timer));
  });

  React.useEffect1(
    () => {
      state.naturalLeap
        ? if (state.currentPhase === State.Work) {
            Notification.notify(
              "Fase concluida",
              "Ative o proximo timer: hora de focar!",
            );
          } else {
            Notification.notify(
              "Fase concluida",
              "Ative o proximo timer e descanse um pouco. Voce merece!",
            );
          }
        : None
    },
    [|state.currentPhase|],
  );

  let toggleIdentifier = "toggle-components";
  let isReseted =
    switch (state.currentPhase, state.seconds) {
    | (Play, seconds) => seconds === state.playTime
    | (Work, seconds) => seconds === state.workTime
    };
  let nonValidTime = state.playTime === 0 || state.workTime === 0;

  <>
    <Component
      width={Some(Component.WidthMedium)}
      padding={Some(Component.PaddingSmall)}>
      <div className=toggleIdentifier>
        <Pomodoro
          seconds={state.seconds}
          currentPhase={state.currentPhase}
          session={state.session}
          maxSessions={state.maxSessions}
          playTime={state.playTime}
          workTime={state.workTime}
          isTicking={state.isTicking}
          reset={_ => dispatch(Reset)}
          stop={_ => dispatch(Stop)}
          start={_ => {
            Notification.requestPermission() |> ignore;
            dispatch(Start);
          }}
          skipTimer={_ => dispatch(SkipTimer)}
        />
      </div>
      <div className=toggleIdentifier hidden=true>
        <Settings
          workTime={state.workTime}
          playTime={state.playTime}
          setWorkTime={time => dispatch(SetTime(Work, time))}
          setPlayTime={time => dispatch(SetTime(Play, time))}
        />
      </div>
      <Toggle
        identifier=toggleIdentifier
        isReseted
        nonValidTime
        onBackToApp={_ => dispatch(Reset)}
      />
    </Component>
    <div
      className="uk-position-bottom-center uk-position-small uk-visible@m uk-position-z-index">
      <Footer />
    </div>
  </>;
};
