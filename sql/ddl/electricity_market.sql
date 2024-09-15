-- data is based off some electricity market data pulled from kaggle
-- https://www.kaggle.com/datasets/jaredandreatta/pjm-and-miso-electricity-market-data?resource=download
-- much of the data is either pricing data or # of MW generated - I picked mostly arbitrary precision
-- numeric columns for them
-- NOTE that the SQL standHEADERard considers numeric columns without a scale to have 0 scale, so this DDL

-- is probably not portable
create table electricity_market (
        "weekday"           smallint,
        on_off              boolean,
        he                  smallint,
        "date"              date,
        date_time           timestamp,
        pjmc_rt_lmp         numeric,
        pjmc_rt_cong        numeric,
        pjmc_da_lmp         numeric,
        pjmc_da_cong        numeric,
        miso_rt_lmp         numeric,
        miso_rt_cong        numeric,
        miso_da_lmp         numeric,
        miso_da_cong        numeric,
        miso_rtload         numeric,
        miso_load_fc        numeric, 
        central_rt_load     numeric, 
        central_load_fc     numeric, 
        miso_gas_gen        numeric,
        miso_da_gas         numeric, 
        miso_coal_gen       numeric, 
        miso_da_coal        numeric,
        miso_nuclear_gen    numeric, 
        miso_nuclear_da     numeric, 
        miso_hydro_gen      numeric,
        mis_da_hydro        numeric,
        pjm_rtload          numeric, 
        pjm_load_fc         numeric, 
        pjm_west_load       numeric, 
        pjm_west_load_fc    numeric,
        pjm_gas_gen         numeric, 
        pjm_coal_gen        numeric, 
        pjm_nuclear_gen     numeric, 
        pjm_hydro_gen       numeric, 
        pjm_ramp_imports    numeric, 
        pjm_ramp_exports    numeric,
        miso_ramp_imports   numeric,
        miso_ramp_exports   numeric,
        miso_ace            numeric,
        pjm_ace             numeric,
        miso_pjmc_dalmp     numeric,
        miso_pjmc_rtlmp     numeric,
        miso_pjmc_da_cong   numeric,
        miso_pjmc_rt_cong   numeric,
        pjm_miso_rt_load    numeric,
        miso_net_load       numeric,
        pjm_net_load        numeric,
        pjm_miso_net_load   numeric
)
